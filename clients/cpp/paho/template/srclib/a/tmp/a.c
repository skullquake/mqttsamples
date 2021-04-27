#include<stdio.h>
#ifdef __cplusplus
extern "C"{
#endif
	/*
static void __attribute__((constructor))startup(void){
	printf("int __attribute__((constructor))init(void)\n");
}
static void __attribute__((destructor))shutdown(void){
	printf("int __attribute__((destructor))decinit(void)\n");
}
	*/
__attribute__((visibility("default")))int appmain(int argc,char*argv[]){
	printf("libb:main:start\n");
	printf("libb:main:end\n");
	return 0;
}
#ifdef __cplusplus
}
#endif
