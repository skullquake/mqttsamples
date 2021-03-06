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
#include"util/util.hpp"
#include"qjs/global.hpp"
#include"app/config/config.hpp"
std::string SERVER_ADDRESS("tcp://localhost:1883");
std::string CLIENT_ID("pahopp_qjs");
std::string TOPIC("cpp_qjs_req");
const int QOS=1;
const int N_RETRY_ATTEMPTS=5;
class action_listener:public virtual mqtt::iaction_listener{
		std::string name_;
		void on_failure(const mqtt::token& tok)override{
			std::cout<<name_<<" failure";
			if(tok.get_message_id()!=0)
				std::cout<<" for token: ["<<tok.get_message_id()<<"]"<< std::endl;
			std::cout<<std::endl;
		}
		void on_success(const mqtt::token&tok)override{
			std::cout<<name_<<" success";
			if(tok.get_message_id()!=0)std::cout<<" for token: ["<<tok.get_message_id()<<"]"<<std::endl;
			auto top=tok.get_topics();
			if(top&&!top->empty())std::cout<<"\ttoken topic: '"<<(*top)[0]<<"', ..."<<std::endl;
			std::cout<<std::endl;
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
			std::cerr<<"Error: "<<exc.what()<<std::endl;
			exit(1);
		}
	}
	void on_failure(const mqtt::token&tok)override{
		std::cout<<"Connection attempt failed"<<std::endl;
		if(++nretry_>N_RETRY_ATTEMPTS)exit(1);
		reconnect();
	}
	void on_success(const mqtt::token&tok)override{}
	void connected(const std::string&cause)override{
		std::cout
			<<"\nConnection success"
			<<"\nSubscribing to topic '"<<TOPIC<<"'\n"
			<<"\tfor client " << CLIENT_ID
			<<" using QoS" << QOS << "\n"
			<<"\nPress Q<Enter> to quit\n"
			<<std::endl
		;
		cli_.subscribe(TOPIC,QOS,nullptr,subListener_);
	}
	void connection_lost(const std::string&cause)override{
		std::cout<<"\nConnection lost"<<std::endl;
		if(!cause.empty())std::cout<<"\tcause: "<<cause<<std::endl;
		std::cout<<"Reconnecting..."<<std::endl;
		nretry_=0;
		reconnect();
	}
	void message_arrived(mqtt::const_message_ptr msg)override{
		std::cout<<">["<<msg->get_topic()<<":"<<msg->to_string()<<"]"<<std::endl;
		{//test json
			app::qjs::Engine qjse;
			{
				qjse.getContext().global()["topic"]=msg->get_topic();
				qjse.getContext().global()["message"]=msg->to_string();
			}
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
			{
				auto&module=qjse.getContext().addModule("Test");
				module.function("test",[](){
				});
			}



			try{
				auto j=nlohmann::json::parse(msg->to_string());
				if(j.contains("path")){
					auto jpath=j["path"];
					if(jpath.is_string()){
						qjse.evalFile(jpath);
					}else{
						std::cerr<<"app::main: error: invalid path specification"<<std::endl;
					}
				}else if(j.contains("script")){
					auto jscript=j["script"];
					if(jscript.is_string()){
						qjse.evalString(jscript);
					}else{
						std::cerr<<"app::main: error: invalid script specification"<<std::endl;
					}
				}else{
					std::cerr<<"app::main: error: no path specified"<<std::endl;
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
int main(int argc,char*argv[]){
	if(argc==2)app::qjs::globalEngine.evalFile(argv[1]);
	//mqtt::async_client cli(SERVER_ADDRESS,CLIENT_ID);
	std::string host;
	{
		std::ostringstream oss;
		oss<<"tcp://"<<app::config::config.get_host()<<":"<<app::config::config.get_port();
		host=oss.str();

	}
	CLIENT_ID=app::config::config.get_clientID();
	TOPIC=app::config::config.get_topic();
	std::cout<<"Connecting to "<<host<<"..."<<std::endl;
	mqtt::async_client cli(host,app::config::config.get_clientID());
	mqtt::connect_options connOpts;
	connOpts.set_clean_session(false);
	callback cb(cli,connOpts);
	cli.set_callback(cb);
	try{
		cli.connect(connOpts,nullptr,cb);
	}catch(const mqtt::exception&exc){
		std::cerr
			<<"ERROR: Unable to connect to MQTT server: '"
			<<SERVER_ADDRESS<<"'"<<exc<<std::endl
		;
		return 1;
	}
	while(std::tolower(std::cin.get())!='q');
	try{
		cli.disconnect()->wait();
	}catch(const mqtt::exception&exc){
		std::cerr<<exc<<std::endl;
		return 1;
	}
 	return 0;
}

