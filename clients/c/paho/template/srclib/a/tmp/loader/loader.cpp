#include<iostream>
#include"./loader.hpp"
#ifdef _WIN32
#include<windows.h>
#elif __DJGPP__
#else
#include"link.h"
#endif
Loader::Loader():dsopath(getDSOPath()){
	//std::cout<<"Loader::Loader::start"<<std::endl;
	std::cout<<dsopath<<":"<<__PRETTY_FUNCTION__<<":start"<<std::endl;
	std::cout<<dsopath<<":"<<__PRETTY_FUNCTION__<<":end"<<std::endl;
	std::cout<<"Loader::Loader::end"<<std::endl;
};
Loader::~Loader(){
	std::cout<<dsopath<<":"<<__PRETTY_FUNCTION__<<":start"<<std::endl;
	std::cout<<dsopath<<":"<<__PRETTY_FUNCTION__<<":end"<<std::endl;
};
std::string Loader::getDSOPath(){
	std::string ret{""};
#ifdef _WIN32
	{
		ret="unimplemented";
		char path[MAX_PATH];
		HMODULE hm = NULL;

		//if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,(LPCSTR) &functionInThisDll, &hm) == 0)
		if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,(LPCSTR) this, &hm) == 0){
		    int ret = GetLastError();
		    fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
		    // Return or however you want to handle an error.
		}
		if (GetModuleFileName(hm, path, sizeof(path)) == 0){
		    int ret = GetLastError();
		    fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
		    // Return or however you want to handle an error.
		}

		// The path variable should now contain the full filepath for this DLL.
		ret=std::string(path);
	}
#elif __DJGPP__
	{
		ret="unimplemented";
	}
#else
	Dl_info i={0};
	int r;
	struct link_map*ei=0;
	void*ptr=(void*)this;//usually some fn ptr
	r=dladdr1(ptr,&i,(void**)&ei,RTLD_DL_LINKMAP);
	if(r){
		//printf("name = %s [%s]\n", i.dli_sname, ei->l_name);
		ret=std::string(ei->l_name);
	}
#endif
	return ret;
}
