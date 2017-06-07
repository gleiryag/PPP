#include<iostream>
#include<vector>
#include"Pipeline.hpp"



int t1(int t){ return t+1; }
int t2(int t){ return t*2; }

int main(){
	std::vector<int> input {1,2,3,4,5};
	std::vector<int> output {};
	

	auto it = std::back_inserter(std::cout);

	simple_pipeline(t1,t2,input,it);


	for(auto x : output) std::cout << x << " " ;


	std::cout << "\n";
}
