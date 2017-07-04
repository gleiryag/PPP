#pragma once
#include<initializer_list>
#include<string>
#include<vector>
#include<sstream>
		
class Header{

	std::vector<std::string> defines;


	public : 

	Header(std::initializer_list<std::string> list){

		for(auto s : list){

			defines.push_back(s);

		}


	}

	void build(std::string& stream){

		for(auto s : defines){
			stream.append("#include<");
			stream.append( s );
			stream.append(">\n");
		}

	}




};
