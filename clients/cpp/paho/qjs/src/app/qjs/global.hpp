#ifndef h4367a444a83111eb8fc1bf7445d7a399
#define h4367a444a83111eb8fc1bf7445d7a399
#include"quickjspp/quickjspp.hpp"
#include"mqtt/async_client.h"
#include<mutex>
namespace app::qjs{
	class Engine{
		public:
			Engine();
			~Engine();
			void evalString(std::string);
			void evalFile(std::string);
			void set_mqtt_client(mqtt::async_client*);
			void init();
			::qjs::Runtime&getRuntime();
			::qjs::Context&getContext();
			JSRuntime*getJSRuntime();
			JSContext*getJSContext();
		private:
			::qjs::Runtime runtime;
			::qjs::Context context;
			::mqtt::async_client*cli;
			JSRuntime*rt;
			JSContext*ctx;
			std::mutex mrun;

	};
	extern Engine globalEngine;
}
#endif

