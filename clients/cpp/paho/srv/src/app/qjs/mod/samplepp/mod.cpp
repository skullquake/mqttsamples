#include"./mod.hpp"
#include<sstream>
#include<algorithm>
#include<cstring>
#include<iostream>
#include"plog/Log.h"
bool app::qjs::mod::samplepp::init(::qjs::Context&context,::std::string modnam){
	bool ret=false;
	try{
		auto&module=context.addModule(modnam.c_str());
		module.function("vv",[](){
			PLOG_DEBUG<<"vv";
		});
		module.function("vs",[](){
			PLOG_DEBUG<<"vs";
			return"foo";
		});
		module.function("ss",[](std::string val){
			PLOG_DEBUG<<"ss";
			return val;
		});
		/*
		std::string s="lorem";
		module.function("css",[&s](){
				return s;
		});
		*/
		::std::ostringstream oss;
		::std::string varnam=modnam;
		std::transform(varnam.begin(),varnam.end(),varnam.begin(),[](unsigned char c){return std::tolower(c);});
		oss<<"import * as "<<varnam<<" from '"<<modnam<<"'"<<std::endl;
		oss<<"globalThis."<<varnam<<"="<<varnam<<";"<<std::endl;
		oss<<std::flush;
		/*
		std::cout<<"----------------------------------------"<<std::endl;
		std::cout<<oss.str()<<std::endl;
		std::cout<<"----------------------------------------"<<std::endl;
		*/
		context.eval(oss.str().c_str(),"<input>",JS_EVAL_TYPE_MODULE);
		ret=true;
	}catch(::qjs::exception){
		auto exc=context.getException();
		std::cerr<<(std::string)exc<<std::endl;
		if((bool)exc["stack"])
			std::cerr<<(std::string)exc["stack"]<<std::endl;
	}
	return ret;
}
