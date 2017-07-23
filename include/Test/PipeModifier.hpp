#pragma once
#include<string>
#include<sstream>
#include<regex>

class PipeModifier{

	std::string name;
	std::string option;
	bool isParallel;
	bool merge;

	public : 

	PipeModifier(){
		isParallel = true;
		name = std::string("p_pipeline");
	}

	PipeModifier(bool isParallel){

		this->isParallel = isParallel;
		
		name = isParallel ? std::string("p_pipeline") : std::string("pipeline");
		option = std::string("");
	}

	PipeModifier(bool isParallel,std::string option){

		this->isParallel = isParallel;
		
		name = isParallel ? std::string("p_pipeline") : std::string("pipeline");
		this->option = !isParallel ? std::string() : option;
	}
	
	PipeModifier(int val, std::string option){

		this->isParallel = true;
		this->merge = true;

		name = std::string("k_pipeline");
		this->option = option.empty() ? std::to_string(val) : std::to_string(val) + "," + option;
	}


	bool is_parallel(){ return isParallel; }
	std::string  get_option(){ return option; }
	std::string get_name(){ 
		std::regex ltgt_regex(">|<|,");
		std::string c_option = std::regex_replace(option,ltgt_regex,"_");
		return name + "_" + c_option;
	}


	void build(std::string& stream){

	
		if(isParallel) stream.append("auto output = ");

		stream.append(name);
		

		if(isParallel && option!="" ){
			
			stream.append("<"); 
			stream.append(option);
			stream.append(">");

		}

	}

};

