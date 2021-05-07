#include"./mod.hpp"
#include<iostream>
#include<sstream>
#include<iomanip>
#include"crow/crow.h"
namespace app::qjs::mod::crow{
	static void write(std::string pSaddr,std::string pVal){
		::crow::response*res=nullptr;{
			unsigned long ul;
			std::istringstream iss(pSaddr);
			iss>>std::hex>>ul;
			res=(::crow::response*)((void*)ul);
		}if(res==nullptr)return;
		res->write(pVal);
	}
	static void end(std::string pSaddr){
		::crow::response*res=nullptr;{
			unsigned long ul;
			std::istringstream iss(pSaddr);
			iss>>std::hex>>ul;
			res=(::crow::response*)((void*)ul);
		}if(res==nullptr)return;
		res->end();
	}
	static void add_header(std::string pSaddr,std::string pHdrK,std::string pHdrV){
		::crow::response*res=nullptr;{
			unsigned long ul;
			std::istringstream iss(pSaddr);
			iss>>std::hex>>ul;
			res=(::crow::response*)((void*)ul);
		}if(res==nullptr)return;
		res->add_header(pHdrK,pHdrV);
	}
	void reg(::qjs::Context&context,const ::crow::request&req,::crow::response&res){
		auto&module=context.addModule("Crow");
		module.function<&write>("write");
		module.function<&end>("end");
		module.function<&add_header>("add_header");

		//module.function("test",[](){});
		//auto cb=[](){};
		//module.function<static_cast<void(*)(void)>(&cb)>("test");

		{//module.add("res",&res);
			std::ostringstream oss;
			oss<<std::hex<<((void*)&res);
			module.add("res",oss.str());
		}

		{//module.add("req",&req);
			std::ostringstream oss;
			oss<<std::hex<<((void*)&res);
			module.add("req",oss.str());
		}
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
