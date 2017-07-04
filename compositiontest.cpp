#include<Pipeline.hpp>


int t1(int t){ return t+1; }
int t3(int t){ return t+1; }

int main(){

	std::vector<int> input{1};
	std::vector<int> output{1};

	auto t2 = [] (int t) { return t*33  ; };

	pipeline(input,std::back_inserter(output),lambdacomposition(t1,t2),t3);


	std::cout << "result = " << output[1] << "\n";

} 
