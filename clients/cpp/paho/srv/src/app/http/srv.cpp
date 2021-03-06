#include"./srv.hpp"
#include"app/config/config.hpp"
#include"app/qjs/global.hpp"
#include"app/qjs/mod/crow/mod.hpp"
#include"app/qjs/mod/crowpp/mod.hpp"
#include"version/version.hpp"
app::http::Server::Server(){
	//crow::App</*MW*/>app;
	CROW_ROUTE(mApp,"/")([](){
		return "test";
	});
	CROW_ROUTE(mApp,"/loglevel")([this](){
		crow::json::wvalue j;
		switch(crow::logger::get_current_log_level()){
			case crow::LogLevel::Debug:
				j["loglevel"]="Debug";
				break;
			case crow::LogLevel::Info:
				j["loglevel"]="Info";
				break;
			case crow::LogLevel::Warning:
				j["loglevel"]="Warning";
				break;
			case crow::LogLevel::Critical:
				j["loglevel"]="Critical";
				break;
			default:
				j["loglevel"]="Invalid";
				break;
		}
		return j;
	});
	CROW_ROUTE(mApp,"/loglevel/<string>")([this](std::string level){
		crow::json::wvalue j;
		j["message"]="loglevel changed";
		      if(level=="debug"){
			mApp.loglevel(crow::LogLevel::Debug);
		}else if(level=="info"){
			mApp.loglevel(crow::LogLevel::Info);
		}else if(level=="warning"){
			mApp.loglevel(crow::LogLevel::Warning);
		}else if(level=="error"){
			mApp.loglevel(crow::LogLevel::Error);
		}else if(level=="critical"){
			mApp.loglevel(crow::LogLevel::Critical);
		}else{
			j["message"]="eloglevel";
		}
		return j;
	});
	CROW_ROUTE(mApp,"/version")([](){
		crow::json::wvalue j;
		j["major"]=::version::getMajor();
		j["minor"]=::version::getMinor();
		j["patch"]=::version::getPatch();
		return j;
	});
	CROW_ROUTE(mApp,"/qjs/<path>")([this](const crow::request&req,crow::response&res,std::string pPath){
		::app::qjs::Engine e;
		::app::qjs::mod::crow::reg(e.getContext(),req,res);
		::app::qjs::mod::crowpp::init(e.getContext(),"Crowpp",mApp,req,res);
		e.evalFile(std::string("./js/")+pPath);
		if(!res.is_completed()){
			crow::json::wvalue j;
			j["status"]="complete";
			//res.add_header("Content-Type","application/json");
			res.add_header("Content-Type","text/plain");
			res.write(j.dump());
			res.end();
		}
	});
	if(app::config::config.get_httpLogLevel()=="info"){
		mApp.loglevel(::crow::LogLevel::Info);
	}else if(app::config::config.get_httpLogLevel()=="debug"){
		mApp.loglevel(::crow::LogLevel::Debug);
	}else if(app::config::config.get_httpLogLevel()=="warning"){
		mApp.loglevel(::crow::LogLevel::Warning);
	}else if(app::config::config.get_httpLogLevel()=="error"){
		mApp.loglevel(::crow::LogLevel::Error);
	}else if(app::config::config.get_httpLogLevel()=="critical"){
		mApp.loglevel(::crow::LogLevel::Critical);
	}else{
		mApp.loglevel(::crow::LogLevel::CRITICAL);
	}
	mApp.port(app::config::config.get_httpPort());
	mApp.multithreaded();
	mApp.concurrency(app::config::config.get_httpConcurrency());
}
app::http::Server::~Server(){
}
void app::http::Server::run(){
	mApp.run();
}
