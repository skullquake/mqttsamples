#include"./global.hpp"
#include"app/config/config.hpp"
#include"./mod/test/mod.hpp"
#include"./mod/test2/mod.hpp"
app::qjs::Engine::Engine():context(runtime),cli(nullptr){
	rt=runtime.rt;
	ctx=context.ctx;
	js_std_init_handlers(rt);
	JS_SetModuleLoaderFunc(rt,nullptr,js_module_loader,nullptr);
	js_std_add_helpers(ctx,0,nullptr);
	js_init_module_std(ctx,"std");
	js_init_module_os(ctx,"os");
	context.eval(R"(
		import * as std from 'std';
		import * as os from 'os';
		globalThis.std = std;
		globalThis.os = os;
	)","<input>",JS_EVAL_TYPE_MODULE);
	app::qjs::mod::test::js_init_module_my_module(ctx,"test");
	app::qjs::mod::test2::js_init_module_my_module(ctx,"test2");
	/*
	{
		auto&module=context.addModule("Config");
		module.function("set_host",[](std::string val){
				app::config::config.set_host(val);
		});
		module.function("set_port",[](int val){
				app::config::config.set_port(val);
		});
		module.function("set_topic",[](std::string val){
				app::config::config.set_topic(val);
		});
		module.function("set_clientID",[](std::string val){
				app::config::config.set_clientID(val);
		});
		module.function("get_host",[](){
				return app::config::config.get_host();
		});
		module.function("get_port",[](){
				return app::config::config.get_port();
		});
		module.function("get_topic",[](){
				return app::config::config.get_topic();
		});
		module.function("get_clientID",[](){
				return app::config::config.get_clientID();
		});
		context.eval(R"(
			import * as config from 'Config';
			globalThis.config = config;
		)","<input>",JS_EVAL_TYPE_MODULE);
	}
	*/
}
app::qjs::Engine::~Engine(){
}
void app::qjs::Engine::set_mqtt_client(mqtt::async_client*pCli){
	cli=pCli;
}
void app::qjs::Engine::evalFile(std::string pPath){
	try{
		context.evalFile(pPath.c_str(),JS_EVAL_TYPE_MODULE);
	}catch(::qjs::exception){
		auto exc=context.getException();
		std::cerr<<(std::string)exc<<std::endl;
		if((bool)exc["stack"])
			std::cerr<<(std::string)exc["stack"]<<std::endl;
	}
}
void app::qjs::Engine::evalString(std::string pSrc){
	std::scoped_lock lock(mrun);
	try{
		context.eval(pSrc.c_str(),"<eval>",JS_EVAL_TYPE_MODULE);
	}catch(::qjs::exception){
		auto exc=context.getException();
		std::cerr<<(std::string)exc<<std::endl;
		if((bool)exc["stack"])
			std::cerr<<(std::string)exc["stack"]<<std::endl;
	}
}
::qjs::Runtime&app::qjs::Engine::getRuntime(){
	return runtime;
}
::qjs::Context&app::qjs::Engine::getContext(){
	return context;
}
::JSRuntime*app::qjs::Engine::getJSRuntime(){
	return rt;
}
::JSContext*app::qjs::Engine::getJSContext(){
	return ctx;
}
namespace app::qjs{
	Engine globalEngine;
}
