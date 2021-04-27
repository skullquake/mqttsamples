#include<iostream>
//#include<thread>
#include<cstdio>
//#include"./loader.hpp"
extern "C"{
//int __attribute__((constructor))startup(void){
static void __attribute__((constructor))startup(void){
	std::cout<<"int __attribute__((constructor))init(void)"<<std::endl;
}
//int __attribute__((destructor))shutdown(void){
static void __attribute__((destructor))shutdown(void){
	std::cout<<"int __attribute__((destructor))decinit(void)"<<std::endl;
}
__attribute__((visibility("default")))int appmain(int argc,char*argv[]){
	std::cout<<"libb:main:start"<<std::endl;
	//std::thread t0([](){
		//std::cout<<"libb:t0:start"<<std::endl;
		//std::cout<<"libb:t0:end"<<std::endl;
	//});
	//t0.join();
	std::cout<<"libb:main:end"<<std::endl;
	return 0;
}
}
//static Loader l;//not destructing on dlclose!
//alternatively...

