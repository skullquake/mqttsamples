#include"./config.hpp"
#include<iostream>
app::config::Config::Config():mHost("localhost"),mPort(1883),mTopic("pahopp_qjs"),mClientID("cpp_qjs_req"){
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
namespace app::config{
	Config config;
}
