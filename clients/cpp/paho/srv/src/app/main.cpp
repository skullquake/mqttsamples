#include<thread>
#include<chrono>
#include"qjs/global.hpp"
#include"app/mqtt/client.hpp"
#include"app/http/srv.hpp"
int main(int argc,char*argv[]){
	if(argc==2)app::qjs::globalEngine.evalFile(argv[1]);
	std::thread t([](){
		app::mqtt::Client c;
		while(true)std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	});
	app::http::Server s;
	s.run();
 	return 0;
}

