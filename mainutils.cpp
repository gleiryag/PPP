#include<mainutils.hpp>

std::string test_prefix = "./test_results/";

void dowork (int weight) {
  int i0;
  int collatz;
  weight *= 10; 
  for (i0=0; i0<weight; i0++) {
		collatz=COLLSEED;
        while (collatz !=1) {
            if (collatz%2==0) {
              collatz = collatz/2;
            } else {
              collatz = 3*collatz+1;
            }
        }
  }
  return ;
}



template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v){
	os << "[ " ;
	for(auto x : v) os << x << " ";
	os << "]" ;
	return os;
}


void initializeArgumentMap(int argc, char* argv[],po::variables_map& vm){
	
	po::options_description desc("Allowed options");
	desc.add_options() ("help", "produce help message")
        ("range", po::value<int>() , "set max size of the testing vector in each experiment")
        ("repetitions", po::value<int>() ,"set the number of repetitions in the experiment")

	;

	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

}

void process_results(std::string name,std::vector<Row> results){

	{ 
		std::ofstream fstream = std::ofstream(test_prefix + name + ".mat");

		fstream << "results = [ ";
		for(auto exp : results )fstream << " [ "<< exp  << " ];\n";
		fstream << " ];";
	
	}




}
