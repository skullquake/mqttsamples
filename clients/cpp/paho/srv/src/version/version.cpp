#include"./version.hpp"
#include"res/res.h"
#include"json/json.hpp"
#include<iostream>
int version::getMajor(){
	int ret=0;
	auto j=nlohmann::json::parse(std::string(binary_src_res_version_json_start,binary_src_res_version_json_end-binary_src_res_version_json_start));
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
	auto j=nlohmann::json::parse(std::string(binary_src_res_version_json_start,binary_src_res_version_json_end-binary_src_res_version_json_start));
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
	auto j=nlohmann::json::parse(std::string(binary_src_res_version_json_start,binary_src_res_version_json_end-binary_src_res_version_json_start));
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
::std::string version::getName(){
	std::string ret="";
	auto j=nlohmann::json::parse(std::string(binary_src_res_meta_json_start,binary_src_res_meta_json_end-binary_src_res_meta_json_start));
	if(j.contains("name")){
		if(j["name"].is_string()){
			ret= j["name"];
		}else{
		}
	}else{
	}
	return ret;
}
::std::string version::getDescription(){
	std::string ret="";
	auto j=nlohmann::json::parse(std::string(binary_src_res_meta_json_start,binary_src_res_meta_json_end-binary_src_res_meta_json_start));
	if(j.contains("description")){
		if(j["description"].is_string()){
			ret= j["description"];
		}else{
		}
	}else{
	}
	return ret;
}
::std::string version::getNotes(){
	std::string ret="";
	auto j=nlohmann::json::parse(std::string(binary_src_res_meta_json_start,binary_src_res_meta_json_end-binary_src_res_meta_json_start));
	if(j.contains("notes")){
		if(j["notes"].is_string()){
			ret= j["notes"];
		}else{
		}
	}else{
	}
	return ret;
}
