#ifndef hfcb36154a99e11ebbc7ca7783a52b5c8
#define hfcb36154a99e11ebbc7ca7783a52b5c8
#include"quickjspp/quickjs/quickjs.h"
#include"quickjspp/quickjs/cutils.h"
namespace app::qjs::mod::test2{
	static JSValue plusNumbers(JSContext*ctx,JSValueConst this_val,int argc,JSValueConst*argv);
	static int js_my_module_init(JSContext*ctx,JSModuleDef*m);
	JSModuleDef*js_init_module_my_module(JSContext*ctx,const char*module_name);
}
#endif
