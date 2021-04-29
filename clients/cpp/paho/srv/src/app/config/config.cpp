#include"./config.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include"json/json.hpp"
app::config::Config::Config():
	mHost("localhost"),
	mPort(1883),
	mTopic("pahopp_qjs"),
	mClientID("cpp_qjs_req"),
	mLogFile("./log.txt")
{
}
app::config::Config::~Config(){
}
void app::config::Config::set_host(std::string pHost){
	mHost=pHost;
}
void app::config::Config::set_port(int pPort){
	mPort=pPort;
}
void app::config::Config::set_topic(std::string pTopic){
	mTopic=pTopic;
}
void app::config::Config::set_clientID(std::string pClientID){
	mClientID=pClientID;
}
void app::config::Config::set_logfile(std::string pLogFile){
	mLogFile=pLogFile;
}

std::string app::config::Config::get_host(){
	return mHost;
}
int app::config::Config::get_port(){
	return mPort;
}
std::string app::config::Config::get_topic(){
	return mTopic;
}
std::string app::config::Config::get_clientID(){
	return mClientID;
}
std::string app::config::Config::get_logfile(){
	return mLogFile;
}
void app::config::Config::loadJson(std::string pPath){
	//std::cout<<"app::config::Config::loadJson(std::string pPath):start"<<std::endl;
	//std::cout<<"app::config::Config::loadJson(std::string pPath):loading "<<pPath<<std::endl;
	try{
		std::ifstream ifs(pPath);
		if(!ifs)throw std::runtime_error(std::string("Failed: to load")+pPath);
		//std::cout<<"app::config::Config::loadJson(std::string pPath):"<<pPath<<" opened"<<std::endl;
		std::stringstream ss;
		ss<<ifs.rdbuf();
		ifs.close();
		std::string strJson=ss.str();
		//std::cout<<strJson<<std::endl;;
		auto j=nlohmann::json::parse(strJson);
		if(j.contains("mqtt")){
			//std::cout<<"mqtt"<<std::endl;
			auto jMqtt=j["mqtt"];
			if(jMqtt.contains("host")){
				//std::cout<<"mqtt:host"<<std::endl;
				auto j=jMqtt["host"];
				if(j.is_string()){
					set_host(j);
				}
			}
			if(jMqtt.contains("port")){
				//std::cout<<"mqtt:port"<<std::endl;
				auto j=jMqtt["port"];
				if(j.is_number()){
					set_port(j);
				}
			}
			if(jMqtt.contains("topic")){
				//std::cout<<"mqtt:topic"<<std::endl;
				auto j=jMqtt["topic"];
				if(j.is_string()){
					set_topic(j);
				}
			}
			if(jMqtt.contains("clientID")){
				//std::cout<<"mqtt:clientID"<<std::endl;
				auto j=jMqtt["clientID"];
				if(j.is_string()){
					set_clientID(j);
				}
			}

		}
		if(j.contains("log")){
			auto jLog=j["log"];
			if(jLog.contains("logfile")){
				auto j=jLog["logfile"];
				if(j.is_string()){
					set_logfile(j);
				}
			}

		}
	}catch(const std::exception&e){
		std::cerr<<"app::config::Config::loadJson(std::string pPath):error:"<<e.what()<<std::endl;
	}
}
void app::config::Config::writeJson(std::string pPath){
}
namespace app::config{
	Config config;
}
