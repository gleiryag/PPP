#pragma once
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<Test/TPipeline.hpp>
class Main {


	std::string main_prefix{"main"};
	int experiment_size, iterations;
	std::string main_body{"main"};
	TPipeline pipe;
	int source_size;
	std::string stabs;
	bool applyTabs;
	std::string name;
	int range;

	public : 

	Main(){ return; };

	Main(int es, int it,int range,TPipeline p, int sz,std::string name) {
		experiment_size = es;
		iterations = it;
		pipe = p;
		source_size=sz;	
		this->name = name;
		this->range = range;
	}

	void build(std::string& stream){

		

		stream.append("int ");
		stream.append(main_prefix); 
		stream.append("(){\n");

		stream.append("\tINT_");
		stream.append(std::to_string(source_size) );
		stream.append(" value = { ");

		for(int i = 0 ; i < source_size ; i++) {
			std::string sep = i ? "," : "";  
			stream.append(sep + std::to_string(i) );
		}
		stream.append("};\n");

		stream.append("\tstd::vector<Row> results{};\n");
		stream.append("\tTimer& timer = Timer::getTimer();\n");
		stream.append("\tfor(int i =0 ; i < " );
		stream.append(std::to_string(iterations) );
		stream.append(" ; i++){\n\t\t");

		if(pipe.is_parallel()){
			stream.append("Source"); 
		}else stream.append("std::vector");

		stream.append("<INT_");
		stream.append(std::to_string(source_size) );
		stream.append("> input");
		if(pipe.is_parallel()) stream.append("{value,value};\n"); 
		else stream.append(";\n");
		stream.append("\t\tRow exp_results=Eigen::VectorXd::Zero(");
		stream.append(std::to_string(experiment_size) );
		stream.append(");\n\n");
		stream.append("\t\tfor(int j = 0 ; j < ");
		stream.append(std::to_string(experiment_size) );
		stream.append(" ; j++){\n");

		if(pipe.is_parallel()){
			stream.append("\t\t\tinput.append(value,"+ std::to_string(range) +");\n");
			stream.append("\t\t\tinput.reset();\n");
		}else {
			stream.append("\t\t\tinput.push_back(value);\n");
		}

		stream.append("\t\t\ttimer.set();\n\t\t\t");
		pipe.build(stream);
		stream.append("\t\t\tdouble elapsed = timer.computeElapsed();\n");
		stream.append("\t\t\texp_results(0,j)=elapsed;\n"); 
		stream.append("\t\t}\n\t\tresults.push_back(exp_results);\n\t");
		stream.append("}\n");
		stream.append("\tprocess_results(\"" + name + "\",results);\n");
		stream.append("}\n");
	}




};
