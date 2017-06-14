#include<iostream>
#include<vector>
#include"Pipeline.hpp"



int t1(int t){
	static int i=0;
	i++;
	return t+i; 
}
int t2(int t){ return t*2; }
int t3(int t){ return t+5; }

void foo(Source<int> source){
	std::cout<< source << "\n";
}


int main(){

	Source<int> source{1,2,3,4,5};
	Source<int> output;

	output = p_pipeline(source,t3,t2,t1) ;

	output.wait();	
	std::cout << "PARALLEL IMP\n";
	std::cout << source << "\n";
	std::cout << output << "\n";

}
