#pragma once
#include<sstream>
#include<string>
#include<stdexcept>
#include<set>
#include<fstream>
#include<iostream>
#include<Test/Header.hpp>
#include<Test/Function.hpp>
#include<Test/Main.hpp>
#include<Test/PipeModifier.hpp>



class Test {


	Header headers{ "mainutils.hpp"};
	std::vector<Function> functions;
	Main main;
	std::string function_prefix{"stage_"};
	int pipe_size;
	int source_size;
	int output_size;
	std::set<int> typedefs;
	std::string program_prefix = "./test_source/";
	std::string test_name;
	std::string program;
	public :

	

	Test(std::vector<int> io_size,int es,int i,std::vector<int> weights,PipeModifier modifier){

		if(io_size.size()<2) throw new std::invalid_argument(std::string("io_size size must be at least 2"));

		pipe_size = io_size.size()-1;

		
		test_name.append("test_");
		test_name.append(std::to_string(pipe_size));
		test_name.append("_");
		test_name.append("_i"+std::to_string(i)+"_s"+std::to_string(es));
		

		if(weights.size()!= pipe_size) throw new std::invalid_argument(std::string("io size is not consistent with weight size"));
		
		
		test_name.append("_w" + std::to_string(weights.front()) + "_" );
		
		source_size = io_size.front();
		
		for(int i = 0; i < pipe_size ; i++){

			int input_size = io_size[i];
			int output_size = io_size[i+1];

			test_name.append(std::to_string(input_size));
			test_name.append("_");
			Function func =  Function(input_size,output_size,weights[i],  function_prefix + std::to_string(i) );
			functions.push_back(func );
		}


		test_name.append(modifier.get_name());
		output_size = io_size.back();

		TPipeline pipe = TPipeline(pipe_size,output_size,function_prefix,modifier);


		for(auto i : io_size) this->typedefs.insert(i);

		main = Main(es,i,pipe,source_size,test_name);

		

	}

	void build(){
		
		headers.build(program);
		program.append("\n\n\n");

		for(auto i : typedefs){
			program.append("using INT_");
			program.append(std::to_string(i));
			program.append(" = struct { int array[");
			program.append(std::to_string(i));
			program.append("]; };\n");
		}
		for(auto& f: functions) f.build(program);
		program.append("\n\n\n");
		main.build(program);


		std::string final_name = program_prefix + test_name;
		std::string command = "g++ -O3 -L ./lib -I ./include mainutils.o timer.o ./lib/libboost_program_options.a " +  final_name + ".cpp -o " + final_name  + " -lpthread";
		

		{ 
		std::ofstream fstream = std::ofstream(final_name + ".cpp");
		fstream << program;
		}

		system( command.c_str() );
		std::cout << command << "\n";

	}


};

