#include"./logger.hpp"

#include"app/config/config.hpp"
#include"plog/Log.h"
#include"plog/Initializers/RollingFileInitializer.h"
#include"plog/Appenders/ConsoleAppender.h"

app::log::Logger::Logger(){}
app::log::Logger::~Logger(){}
void app::log::Logger::initialize(std::string pLogFile){
	//app::config::config.get_loadJson("./config.json");
	//static plog::RollingFileAppender<plog::CsvFormatter> csvFileAppender("log.csv");
	static ::plog::RollingFileAppender<plog::TxtFormatter> txtFileAppender(pLogFile.c_str());
	static ::plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug,&consoleAppender)
		.addAppender(&txtFileAppender);//only one?
		//.addAppender(&csvFileAppender);
	PLOG_INFO<<"Logger connected ["<<pLogFile<<"]"<<std::endl;
	//plog::init(plog::debug,"log.txt");
	/*
	PLOG_VERBOSE<<"PLOG_VERBOSE";
	PLOG_DEBUG<<"PLOG_DEBUG";
	PLOG_INFO<<"PLOG_INFO";
	PLOG_WARNING<<"PLOG_WARNING";
	PLOG_ERROR<<"PLOG_ERROR";
	PLOG_FATAL<<"PLOG_FATAL";
	PLOG_NONE<<"PLOG_NONE";
	*/
}
namespace app::log{
	Logger logger;
}
