#include"./srv.hpp"
app::http::Server::Server(){
	//crow::App</*MW*/>app;
	CROW_ROUTE(mApp,"/")([](){
		return "test";
	});
/*
namespace crow
{
    enum class LogLevel
    {
#ifndef ERROR
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
#endif
*/
	mApp.loglevel(::crow::LogLevel::CRITICAL);
	mApp.port(8089);
	mApp.multithreaded();
	//mApp.concurrency(4);
}
app::http::Server::~Server(){
}
void app::http::Server::run(){
	mApp.run();
}
