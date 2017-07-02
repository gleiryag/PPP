#include<string>
#include <Eigen/Dense>
#include<Timer.hpp>
#include<iostream>
#include<vector>
#include<Pipeline.hpp>
#include<fstream>
#include <boost/program_options.hpp>

#define PINNING_STRATEGY ConditionalPinning<1>
constexpr int COLLSEED =  827381;

void dowork (int weight) {
  int i0, i1;
  int collatz;

  for (i0=0; i0<weight; i0++) {
    for (i1=0; i1<weight; i1++) {
          collatz=COLLSEED;
          while (collatz !=1) {
            if (collatz%2==0) {
              collatz = collatz/2;
            } else {
              collatz = 3*collatz+1;
            }
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
