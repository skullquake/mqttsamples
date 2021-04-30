#include"./mod.hpp"
#include<iostream>
namespace app::qjs::mod::crow{
	static void f0(){
		std::cout<<"app::qjs::mod::crow::f0:start"<<std::endl;
	}
	static void write(){
		std::cout<<"app::qjs::mod::crow::f0:start"<<std::endl;
	}
	static void add_header(){
		std::cout<<"app::qjs::mod::crow::f0:start"<<std::endl;
	}
	void reg(::qjs::Context&context,const ::crow::request&req,::crow::response&res){
		std::cout<<"app::qjs::mod::crow::reg:start"<<std::endl;
		auto&module=context.addModule("Crow");
		module.function<&f0>("f0");
		module.function<&write>("write");
		module.function<&add_header>("add_header");
		module.function("test",[](){});
		module.add("res",&res);
		module.add("req",&req);
		context.eval(
			R"(
				import*as crow from'Crow';
				globalThis.crow=crow;
			)",
			R"(<import>)",
			JS_EVAL_TYPE_MODULE
		);
	}
	/*
	static JSValue plusNumbers(JSContext*ctx,JSValueConst this_val,int argc,JSValueConst*argv){
		int a,b;
		if(JS_ToInt32(ctx,&a,argv[0]))
			return JS_EXCEPTION;
		if(JS_ToInt32(ctx,&b,argv[1]))
			return JS_EXCEPTION;
		return JS_NewInt32(ctx,a+b);
	}
	static const JSCFunctionListEntry js_my_module_funcs[]={
		JS_CFUNC_DEF("plus",2,plusNumbers),
	};
	static int js_my_module_init(JSContext*ctx,JSModuleDef*m){
		return JS_SetModuleExportList(ctx,m,js_my_module_funcs,countof(js_my_module_funcs));
	}
	JSModuleDef*js_init_module_my_module(JSContext*ctx,const char*module_name){
		JSModuleDef*m;
		m=JS_NewCModule(ctx,module_name,js_my_module_init);
		if(!m)
			return NULL;
		JS_AddModuleExportList(ctx,m,js_my_module_funcs,countof(js_my_module_funcs));
		return m;
	}
	*/
}
