#pragma once
#include<string>
#include<sstream>

class PipeModifier{

	std::string name;
	std::string option;
	bool isParallel;

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
		option = isParallel ? std::string() : option;
	}


	bool is_parallel(){ return isParallel; }
	std::string  get_option(){ return option; };


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

