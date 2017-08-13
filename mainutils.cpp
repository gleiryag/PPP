#include<mainutils.hpp>

std::string test_prefix = "./test_results/";

void dowork (int weight) {

  int k=22;
  int p;  
  for(int i=0;i<weight;i++){
	for(int j =0;j<10000;j++){
		k++;
	}
	}

  p = k;
  return ;
}



template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v){
	os << "[ " ;
	for(auto x : v) os << x << ",";
	os << "]" ;
	return os;
}


void process_results(std::string name,std::vector<Row> results){

	{ 
		std::ofstream fstream = std::ofstream(test_prefix + name + ".m");

		fstream << "[ ";
		for(auto exp : results )fstream << " [ "<< exp  << " ],\n";
		fstream << " ],";
	
	}




}
