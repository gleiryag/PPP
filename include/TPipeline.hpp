#pragma once
#include<string>
#include<sstream>
#include<PipeModifier.hpp>
class TPipeline{


	int size;
	int o_size;
	std::string pf;
	PipeModifier modifier;


	public : 



	TPipeline(){ return; };

	TPipeline(int s,int os, std::string prefix,PipeModifier& mod){

		size = s;
		pf = prefix;
		modifier = mod;
		o_size = os;

	}


	bool is_parallel(){ return modifier.is_parallel(); }

	void build(std::string& stream){

		if(!is_parallel()){
			stream.append("auto output = std::vector<INT_");
			stream.append(std::to_string(o_size));
			stream.append(">();\n");
		}
		modifier.build(stream);
		stream.append("(input");

		if(!is_parallel()) stream.append(",std::back_inserter(output)");

		for(int i = 0 ; i < size ; i++ ){



			stream.append(","); 
			stream.append(pf );
			stream.append(std::to_string(i));

		}

		stream.append(");\n");


		if(is_parallel()) stream.append("\t\t\toutput.wait();\n");

	}


};
