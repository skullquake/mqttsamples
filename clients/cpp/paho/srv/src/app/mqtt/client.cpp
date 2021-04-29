#include"./client.hpp"
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cctype>
#include<thread>
#include<chrono>
#include<sstream>
#include<cstdio>
#include<cstring>
#include"quickjspp/quickjspp.hpp"
#include"json/json.hpp"
#include"mqtt/async_client.h"
#include"app/util/util.hpp"
#include"app/qjs/global.hpp"
#include"app/config/config.hpp"
#include"app/log/logger.hpp"
std::string SERVER_ADDRESS("tcp://localhost:1883");
std::string CLIENT_ID("pahopp_qjs");
std::string TOPIC("cpp_qjs_req");
int QOS=1;
int N_RETRY_ATTEMPTS=5;
class action_listener:public virtual mqtt::iaction_listener{
		std::string name_;
		void on_failure(const mqtt::token& tok)override{
			PLOG_ERROR<<"failure";
			//std::cout<<name_<<" failure";
			if(tok.get_message_id()!=0)
				//std::cout<<" for token: ["<<tok.get_message_id()<<"]"<< std::endl;
				PLOG_ERROR<<" for token: ["<<tok.get_message_id()<<"]";
			//std::cout<<std::endl;
		}
		void on_success(const mqtt::token&tok)override{
			//std::cout<<name_<<" success";
			PLOG_INFO<<name_<<" success";
			if(tok.get_message_id()!=0)
				//std::cout<<" for token: ["<<tok.get_message_id()<<"]"<<std::endl;
				PLOG_INFO<<" for token: ["<<tok.get_message_id()<<"]";
			auto top=tok.get_topics();
			if(top&&!top->empty())
				//std::cout<<"\ttoken topic: '"<<(*top)[0]<<"', ..."<<std::endl;
				PLOG_INFO<<"\ttoken topic: '"<<(*top)[0]<<"', ...";
			//std::cout<<std::endl;
		}
	public:
		action_listener(const std::string&name):name_(name){}
};
class callback:public virtual mqtt::callback,public virtual mqtt::iaction_listener{
	int nretry_;
	mqtt::async_client& cli_;
	mqtt::connect_options& connOpts_;
	action_listener subListener_;
	void reconnect(){
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		try{
			cli_.connect(connOpts_,nullptr,*this);
		}catch(const mqtt::exception&exc){
			//std::cerr<<"Error: "<<exc.what()<<std::endl;
			PLOG_ERROR<<"Error: "<<exc.what();
			exit(1);
		}
	}
	void on_failure(const mqtt::token&tok)override{
		PLOG_ERROR<<"Connection attempt failed";
		if(++nretry_>N_RETRY_ATTEMPTS)exit(1);
		reconnect();
	}
	void on_success(const mqtt::token&tok)override{}
	void connected(const std::string&cause)override{
		PLOG_INFO<<"Connection success";
		PLOG_INFO<<"Subscribing to topic '"<<TOPIC;
		PLOG_INFO<<"for client " << CLIENT_ID;
		PLOG_INFO<<"using QoS" << QOS;
		PLOG_INFO<<"Press Q<Enter> to quit";
		cli_.subscribe(TOPIC,QOS,nullptr,subListener_);
	}
	void connection_lost(const std::string&cause)override{
		PLOG_INFO<<"Connection lost";
		if(!cause.empty())PLOG_ERROR<<"cause: "<<cause;
		PLOG_INFO<<"Reconnecting...";
		nretry_=0;
		reconnect();
	}
	void message_arrived(mqtt::const_message_ptr msg)override{
		PLOG_INFO<<">["<<msg->get_topic()<<":"<<msg->to_string()<<"]";
		{//test json
			app::qjs::Engine qjse;
			{
				qjse.getContext().global()["topic"]=msg->get_topic();
				qjse.getContext().global()["message"]=msg->to_string();
			}
			/*
			{
				auto&module=qjse.getContext().addModule("Mqtt");
				module.function("publish",[this](std::string topic,std::string payload){
					//if(cli!=nullptr){
						try{
							auto msg_res=mqtt::make_message(topic.c_str(),payload.c_str());
							msg_res->set_qos(1);
							cli_.publish(msg_res);
						}catch(const std::exception&e){
							std::cerr<<e.what()<<std::endl;
						}
					//}
				});
				qjse.getContext().eval(R"(
					import * as mqtt from 'Mqtt';
					globalThis.mqtt = mqtt;
				)","<input>",JS_EVAL_TYPE_MODULE);
			}
			*/
			/*
			{
				auto&module=qjse.getContext().addModule("Test");
				module.function("test",[](){
				});
			}
			*/
			try{
				auto j=nlohmann::json::parse(msg->to_string());
				if(j.contains("path")){
					auto jpath=j["path"];
					if(jpath.is_string()){
						qjse.evalFile(jpath);
					}else{
						PLOG_ERROR<<"app::main: error: invalid path specification";
					}
				}else if(j.contains("script")){
					auto jscript=j["script"];
					if(jscript.is_string()){
						qjse.evalString(jscript);
					}else{
						PLOG_ERROR<<"app::main: error: invalid script specification";
					}
				}else{
					PLOG_ERROR<<"app::main: error: no path specified";
				}
			}catch(const std::exception&e){
				{
					qjse.set_mqtt_client(&cli_);
					qjse.evalString(msg->to_string());
				}
			
			}

		}
	}
	void delivery_complete(mqtt::delivery_token_ptr token)override{}
public:
	callback(mqtt::async_client&cli,mqtt::connect_options&connOpts):nretry_(0),cli_(cli),connOpts_(connOpts),subListener_("Subscription"){}
};
app::mqtt::Client::Client()
{
	std::string host;
	{
		std::ostringstream oss;
		oss<<"tcp://"<<::app::config::config.get_host()<<":"<<::app::config::config.get_port();
		host=oss.str();

	}
	CLIENT_ID=::app::config::config.get_clientID();
	TOPIC=::app::config::config.get_topic();
	PLOG_INFO<<"Connecting to "<<host<<"...";
	//::mqtt::async_client cli("tcp://localhost:1883","ES");
	cli=new ::mqtt::async_client(host,app::config::config.get_clientID());
	::mqtt::connect_options connOpts;
	connOpts.set_clean_session(false);
	callback cb(*cli,connOpts);
	cli->set_callback(cb);
	try{
		cli->connect(connOpts,nullptr,cb);
	}catch(const ::mqtt::exception&exc){
		PLOG_ERROR
			<<"ERROR: Unable to connect to MQTT server: '"
			<<SERVER_ADDRESS<<"'"<<exc;
		;
		//return 1;
	}
}
app::mqtt::Client::~Client(){
	try{
		cli->disconnect()->wait();
	}catch(const ::mqtt::exception&exc){
		PLOG_ERROR<<exc;
	}
}
