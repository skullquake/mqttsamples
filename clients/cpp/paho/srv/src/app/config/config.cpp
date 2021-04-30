#include"./config.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include"json/json.hpp"
#include"plog/Log.h"
app::config::Config::Config():
	mMqttHost("localhost"),
	mMqttPort(1883),
	mMqttTopic("pahopp_qjs"),
	mMqttClientID("cpp_qjs_req"),
	mHttpHost("0.0.0.0"),
	mHttpPort(8080),
	mLogFile("./log.txt")
{
}
app::config::Config::~Config(){
}
void app::config::Config::set_mqttHost(std::string pMqttHost){
	mMqttHost=pMqttHost;
}
void app::config::Config::set_mqttPort(int pMqttPort){
	mMqttPort=pMqttPort;
}
void app::config::Config::set_mqttTopic(std::string pMqttTopic){
	mMqttTopic=pMqttTopic;
}
void app::config::Config::set_mqttClientID(std::string pMqttClientID){
	mMqttClientID=pMqttClientID;
}
void app::config::Config::set_httpHost(std::string pHttpHost){
	mHttpHost=pHttpHost;
}
void app::config::Config::set_httpPort(int pHttpPort){
	mHttpPort=pHttpPort;
}
void app::config::Config::set_httpLogLevel(std::string pHttpLogLevel){
	mHttpLogLevel=pHttpLogLevel;
}
void app::config::Config::set_httpConcurrency(int pHttpConcurrency){
	mHttpConcurrency=pHttpConcurrency;
}
void app::config::Config::set_logFile(std::string pLogFile){
	mLogFile=pLogFile;
}

std::string app::config::Config::get_mqttHost(){
	return mMqttHost;
}
int app::config::Config::get_mqttPort(){
	return mMqttPort;
}
std::string app::config::Config::get_mqttTopic(){
	return mMqttTopic;
}
std::string app::config::Config::get_mqttClientID(){
	return mMqttClientID;
}
std::string app::config::Config::get_httpHost(){
	return mHttpHost;
}
int app::config::Config::get_httpPort(){
	return mHttpPort;
}
std::string app::config::Config::get_httpLogLevel(){
	return mHttpLogLevel;
}
int app::config::Config::get_httpConcurrency(){
	return mHttpConcurrency;
}

std::string app::config::Config::get_logFile(){
	return mLogFile;
}
void app::config::Config::loadJson(std::string pPath){
	try{
		std::ifstream ifs(pPath);
		if(!ifs)throw std::runtime_error(std::string("Failed: to load")+pPath);
		std::stringstream ss;
		ss<<ifs.rdbuf();
		ifs.close();
		std::string strJson=ss.str();
		auto j=nlohmann::json::parse(strJson);
		if(j.contains("mqtt")){
			auto jMqtt=j["mqtt"];
			if(jMqtt.contains("host")){
				auto j=jMqtt["host"];
				if(j.is_string()){
					set_mqttHost(j);
				}
			}
			if(jMqtt.contains("port")){
				auto j=jMqtt["port"];
				if(j.is_number()){
					set_mqttPort(j);
				}
			}
			if(jMqtt.contains("topic")){
				auto j=jMqtt["topic"];
				if(j.is_string()){
					set_mqttTopic(j);
				}
			}
			if(jMqtt.contains("clientID")){
				auto j=jMqtt["clientID"];
				if(j.is_string()){
					set_mqttClientID(j);
				}
			}
		}
		if(j.contains("log")){
			auto jLog=j["log"];
			if(jLog.contains("logfile")){
				auto j=jLog["logfile"];
				if(j.is_string()){
					set_logFile(j);
				}
			}
		}
		if(j.contains("http")){
			auto jLog=j["http"];
			if(jLog.contains("host")){
				auto j=jLog["host"];
				if(j.is_string()){
					set_httpHost(j);
				}else{
					PLOG_ERROR<<"failed to obtain port";
				}
			}
			if(jLog.contains("port")){
				auto j=jLog["port"];
				if(j.is_number()){
					PLOG_INFO<<"port:"<<(int)j;
					set_httpPort(j);
				}else{
					PLOG_ERROR<<"invalid port specification";
				}
			}else{
					PLOG_ERROR<<"failed to obtain port";
			}
			if(jLog.contains("loglevel")){
				auto j=jLog["loglevel"];
				if(j.is_string()){
					set_httpLogLevel(j);
				}
			}
			if(jLog.contains("concurrency")){
				auto j=jLog["concurrency"];
				if(j.is_number()){
					set_httpConcurrency(j);
				}
			}

		}else{
				PLOG_ERROR<<"failed to obtain http configuration";
		}
	}catch(const std::exception&e){
		PLOG_ERROR<<e.what();
	}
}
void app::config::Config::writeJson(std::string pPath){
}
namespace app::config{
	Config config;
}
