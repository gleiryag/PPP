#pragma once
#include<string>
#include<vector>
#include<sstream>

class Function {


	int input_size ;
	int output_size;
	int work;
	std::string name;

	public : 

	Function(int is,int os, int w,std::string n): input_size{is},output_size{os},work{w},name{n}{  return ; }


	void build(std::string& stream){

		stream.append("INT_");
		stream.append(std::to_string(output_size));
		stream.append(" ");
		stream.append(name);
		stream.append("( INT_"); 
		stream.append(std::to_string(input_size)); 
		stream.append(" input){ dowork(");
		stream.append(std::to_string(work));
		stream.append(") ; return input; }\n");    

	}


};
