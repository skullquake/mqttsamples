#include<thread>
#include<chrono>
#include"qjs/global.hpp"
#include"app/mqtt/client.hpp"
#include"app/http/srv.hpp"
#include"app/config/config.hpp"
#include"app/log/logger.hpp"
#include"version/version.hpp"
#include<iostream>
int main(int argc,char*argv[]){
	std::cout
		<<version::getName()<<" ["<<version::getDescription()<<"]: Version "
		<<version::getMajor()<<"."
		<<version::getMinor()<<"."
		<<version::getPatch()<<std::endl
		<<"( "<<version::getNotes()<<" )"<<std::endl
		<<std::endl;
	app::config::config.loadJson("./config.json");
	app::log::logger.initialize(app::config::config.get_logFile());
	//if(argc==2)app::qjs::globalEngine.evalFile(argv[1]);
	PLOG_DEBUG<<"starting mqtt client";
	std::thread t([](){
		app::mqtt::Client c;
		while(true)std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	});
	app::http::Server s;
	s.run();
	//t.join();
 	return 0;
}

