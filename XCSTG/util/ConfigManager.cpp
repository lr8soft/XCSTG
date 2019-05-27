#pragma once
#ifndef _config_manager_
#define _config_manager_
#include "ConfigManager.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;
xc_std::ConfigManager::ConfigManager(string file_path):info_path(file_path){
	load_from_file();
}
bool xc_std::ConfigManager::add_new_info(string key, string value){
	auto ret=map_info.emplace(key,value);
	save_to_file();
	return ret.second;
}
bool xc_std::ConfigManager::delete_old_info(string key) {
	auto ret=map_info.erase(key) ? true : false;
	save_to_file();
	return ret;
}
bool xc_std::ConfigManager::replace_old_info(string key, string value){
	if(!find_key_exist(key))
		return false;
	else {
		map_info[key] = value;
		save_to_file();
		return true;
	}
}
stringstream xc_std::ConfigManager::get_value(string key){
	stringstream ret;
	if(find_key_exist(key)){
		auto t_pair=map_info.find(key);
		ret<<t_pair->second;
	}
	return ret;
}
bool xc_std::ConfigManager::load_from_file(){
	ifstream file_io(info_path, ios::in);
	if (!file_io) {
		return false;
	}
	else {
		load_to_pair(file_io);
		file_io.close();
		return true;
	}
}
bool xc_std::ConfigManager::save_to_file(){
	ofstream file_io(info_path,ios::out);
	if (!file_io) 
		return false;
	else {
		for (auto element = map_info.begin(); element != map_info.end();element++) {
			string head_key = element->first;
			string tail_key = element->second;
			file_io << '[' << head_key << "]=["<< tail_key << ']' << endl;
		}
		file_io.close();
		return true;
	}

}
bool xc_std::ConfigManager::find_key_exist(string key){
	return !(map_info.find(key)==map_info.end());
}
void xc_std::ConfigManager::load_to_pair(ifstream& input_io){
	string file_info,io_temp;
	while (getline(input_io, io_temp))
		file_info += io_temp;
	string head_temp, tail_temp;
	size_t split_counter=0;
	for (size_t head_ptr = file_info.find('[', 0), tail_ptr = file_info.find(']', head_ptr);
		head_ptr != string::npos&&tail_ptr != string::npos; 
		head_ptr = file_info.find('[', tail_ptr),tail_ptr= file_info.find(']', head_ptr)) {
		string temp_value = file_info.substr(head_ptr+1, tail_ptr-head_ptr-1);
		if (split_counter % 2 == 0)
			head_temp = temp_value;
		else {
			tail_temp = temp_value;
			map_info[head_temp] = tail_temp;
		}
		split_counter++;
	}
}
#endif /*_config_manager_*/