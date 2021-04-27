#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cctype>
#include<thread>
#include<chrono>
#include"mqtt/async_client.h"
#include"util.hpp"
const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("pahopp");
const std::string TOPIC("cpp_exec_req");
const int QOS = 1;
const int N_RETRY_ATTEMPTS = 5;
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
		{
			std::string execres=exec(msg->to_string());
			auto msg_res=mqtt::make_message("cpp_exec_res"/*topic*/,execres.c_str()/*payload*/);
			msg_res->set_qos(QOS);
			cli_.publish(msg_res);
		}
	}
	void delivery_complete(mqtt::delivery_token_ptr token)override{}
public:
	callback(mqtt::async_client&cli,mqtt::connect_options&connOpts):nretry_(0),cli_(cli),connOpts_(connOpts),subListener_("Subscription"){}
};
int main(int argc,char*argv[]){
	mqtt::async_client cli(SERVER_ADDRESS,CLIENT_ID);
	mqtt::connect_options connOpts;
	connOpts.set_clean_session(false);
	callback cb(cli,connOpts);
	cli.set_callback(cb);
	try{
		std::cout<<"Connecting to the MQTT server..."<<std::flush;
		cli.connect(connOpts,nullptr,cb);
	}catch(const mqtt::exception&exc){
		std::cerr
			<<"\nERROR: Unable to connect to MQTT server: '"
			<<SERVER_ADDRESS<<"'"<<exc<<std::endl
		;
		return 1;
	}
	while(std::tolower(std::cin.get())!='q');//heavy
	try{
		std::cout<<"\nDisconnecting from the MQTT server..."<<std::flush;
		cli.disconnect()->wait();
		std::cout<<"OK"<<std::endl;
	}catch(const mqtt::exception&exc){
		std::cerr<<exc<<std::endl;
		return 1;
	}
 	return 0;
}
