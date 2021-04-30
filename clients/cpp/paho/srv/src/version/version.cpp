#include"./version.hpp"
#include"res/res.h"
#include"json/json.hpp"
#include<iostream>
int version::getMajor(){
	int ret=0;
	auto j=nlohmann::json::parse(binary_src_res_version_json_start);
	if(j.contains("major")){
		if(j["major"].is_number()){
			ret= j["major"];
		}else{
			ret=-1;
		}
	}else{
		ret=-1;
	}
	return ret;
}
int version::getMinor(){
	int ret=0;
	auto j=nlohmann::json::parse(binary_src_res_version_json_start);
	if(j.contains("minor")){
		if(j["minor"].is_number()){
			ret= j["minor"];
		}else{
			ret=-1;
		}
	}else{
		ret=-1;
	}
	return ret;

}
int version::getPatch(){
	int ret=0;
	auto j=nlohmann::json::parse(binary_src_res_version_json_start);
	if(j.contains("patch")){
		if(j["patch"].is_number()){
			ret= j["patch"];
		}else{
			ret=-1;
		}
	}else{
		ret=-1;
	}
	return ret;
}
