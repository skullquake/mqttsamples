#ifndef h1b7b3ebaa99d11eba6bbc3a22ff5fcdf
#define h1b7b3ebaa99d11eba6bbc3a22ff5fcdf
#include"quickjspp/quickjs/quickjs.h"
#include"quickjspp/quickjs/cutils.h"
namespace app::qjs::mod::sample{
	static JSValue plusNumbers(JSContext*ctx,JSValueConst this_val,int argc,JSValueConst*argv);
	static int js_my_module_init(JSContext*ctx,JSModuleDef*m);
	JSModuleDef*js_init_module_my_module(JSContext*ctx,const char*module_name);
}
#endif
