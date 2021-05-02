#include"./mod.hpp"
#include<sstream>
#include<algorithm>
#include<cstring>
#include<iostream>
#include"plog/Log.h"
bool app::qjs::mod::crowpp::init(::qjs::Context&context,::std::string modnam,::crow::SimpleApp&app,const crow::request&req,crow::response&res){
	bool ret=false;
	try{
		auto&module=context.addModule(modnam.c_str());
		module.function("write",[&res](std::string val){
			PLOG_DEBUG<<"write";
			res.write(val);
		});
		module.function("end",[&res](){
			PLOG_DEBUG<<"end";
			res.end();
		});
		module.function("add_header",[&res](::std::string k,::std::string v){
			PLOG_DEBUG<<"add_header";
			res.add_header(k,v);
		});
		module.function("get_header_value",[&req](::std::string k){
			PLOG_DEBUG<<"get_header_value";
			return req.get_header_value(k);
		});
		/*
		module.function("get_headers",[&req](){
			PLOG_DEBUG<<"get_headers";
			return req.headers;
		});
		*/
		module.function("set_static_file_info",[&res](::std::string path){
			PLOG_DEBUG<<"set_static_file_info";
			return res.set_static_file_info(path);
		});
		module.function("raw_url",[&req](){
			PLOG_DEBUG<<"raw_url";
			return req.raw_url;
		});
		module.function("get_method",[&req](){
			PLOG_DEBUG<<"method";
			return ::crow::method_name(req.method);
		});

		module.function("url",[&req](){
			PLOG_DEBUG<<"url";
			return req.url;
		});
		module.function("remoteIpAddress",[&req](){
			PLOG_DEBUG<<"remoteIpAddress";
			return req.remoteIpAddress;
		});
		/* linker errot on traits on returning map
		module.function("url_params",[&req](){
			PLOG_DEBUG<<"url_params";
			::std::map<::std::string,std::string>ret;
			//return ret;
			//return req.url_params.get_dict();
		});
		*/
		module.function("get_url_param",[&req](::std::string k){
			PLOG_DEBUG<<"get_url_param";
			auto c=req.url_params.get(k);
			return c==nullptr?std::string(""):std::string(c);
		});
		module.function("get_body",[&req](){
			PLOG_DEBUG<<"get_body";
			return req.body;
		});

		module.function("set_loglevel",[&app](::std::string level){
			PLOG_DEBUG<<"set_loglevel";
			      if(level=="debug"){
				app.loglevel(crow::LogLevel::Debug);
			}else if(level=="info"){
				app.loglevel(crow::LogLevel::Info);
			}else if(level=="warning"){
				app.loglevel(crow::LogLevel::Warning);
			}else if(level=="error"){
				app.loglevel(crow::LogLevel::Error);
			}else if(level=="critical"){
				app.loglevel(crow::LogLevel::Critical);
			}else{
			}
		});
		module.function("get_loglevel",[&app]()->::std::string{
			PLOG_DEBUG<<"get_loglevel";
			switch(::crow::logger::get_current_log_level()){
				case crow::LogLevel::Debug:
					return "eebug";
				case crow::LogLevel::Info:
					return "info";
					break;
				case crow::LogLevel::Warning:
					return "warning";
					break;
				case crow::LogLevel::Error:
					return "error";
					break;
				case crow::LogLevel::Critical:
					return "critical";
					break;
				default:
					return "invalid";
					break;
			}
		});
		module.function("set_port",[&app](int port){
			PLOG_DEBUG<<"set_port";
			app.port(port);
		});
		module.function("set_timeout",[&app](int timeout){
			PLOG_DEBUG<<"set_timeout";
			app.timeout(timeout);
		});
		module.function("set_server_name",[&app](::std::string server_name){
			PLOG_DEBUG<<"set_server_name";
			app.server_name(server_name);
		});
		module.function("set_bindaddr",[&app](::std::string bindaddr){
			PLOG_DEBUG<<"set_bindaddr";
			app.bindaddr(bindaddr);
		});
		module.function("set_multithreaded",[&app](){
			PLOG_DEBUG<<"set_multithreaded";
			app.multithreaded();
		});
		module.function("set_concurrency",[&app](int concurrency){
			PLOG_DEBUG<<"set_concurrency";
			app.concurrency(concurrency);
		});
		module.function("run",[&app](){
			PLOG_DEBUG<<"run";
			app.run();
		});
		module.function("stop",[&app](){
			PLOG_DEBUG<<"stop";
			app.stop();
		});




		::std::ostringstream oss;
		::std::string varnam=modnam;
		std::transform(varnam.begin(),varnam.end(),varnam.begin(),[](unsigned char c){return std::tolower(c);});
		oss<<"import * as "<<varnam<<" from '"<<modnam<<"'"<<std::endl;
		oss<<"globalThis."<<varnam<<"="<<varnam<<";"<<std::endl;
		oss<<std::flush;
		context.eval(oss.str().c_str(),"<input>",JS_EVAL_TYPE_MODULE);
		ret=true;
	}catch(::qjs::exception){
		auto exc=context.getException();
		PLOG_ERROR<<(std::string)exc<<std::endl;
		if((bool)exc["stack"])
			PLOG_ERROR<<(std::string)exc["stack"]<<std::endl;
	}
	return ret;
}
