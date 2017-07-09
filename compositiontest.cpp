#include<Pipeline.hpp>

int t1(int t){ return t+1; }
int t3(int t){ return t+1; }

int main(){

	std::vector<int> input{1};
	std::vector<int> output{1};

	auto t2 = [] (int t) { return t*2  ; };

	auto f_sequence = make_sequence(t1,t2,t3);
	auto f = f_sequence.stage<0,2>();

	pipeline(input,std::back_inserter(output),f);

	

	std::cout << "result = " << output[1] << "\n";
	std::cout << "result = " << f(2) << "\n";

	Source<int> input_s{1,2,3};

	k_pipeline<2>(input_s,t1,t2,t3);

} 
