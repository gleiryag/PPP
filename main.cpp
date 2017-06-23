#include<iostream>
#include<vector>
#include"Pipeline.hpp"
#include<fstream>
#include <Eigen/Dense>

using Eigen::Matrix;

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

constexpr int w = 100;

int t1(int t){ dowork(w); return t+1; }
int t2(int t){ dowork(w); return t*2; }
int t3(int t){ dowork(w); return t*2; }
int t4(int t){ dowork(w); return t+5; }

void foo(Source<int> source){
	std::cout<< source << "\n";
}

template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v){
	os << "[ " ;
	for(auto x : v) os << x << " ";
	os << "]" ;
	return os;
}

double computeElapsed(){

	 return ((Tpf->tv_sec-Tps->tv_sec)*1000000 + Tpf->tv_usec-Tps->tv_usec)/ (double)1000000;

}

int main(){



	Tps = (struct timeval*) malloc(sizeof(struct timeval));
	Tpf = (struct timeval*) malloc(sizeof(struct timeval));
	Tzp = 0;

	constexpr int range = 50;
	constexpr int repteitions = 1;
	

	Matrix<double,1,range> results_cpu1=Matrix<double,1,range>::Zero();
	Matrix<double,1,range> results_cpu2=Matrix<double,1,range>::Zero();
	Matrix<double,1,range> results_cpu3=Matrix<double,1,range>::Zero();
	Matrix<double,1,range> results_cpu4=Matrix<double,1,range>::Zero();
	Matrix<double,1,range> serial_results=Matrix<double,1,range>::Zero();

	for(int j =0;j<repteitions;j++){

		Source<int> input(true);

		for(int i=0;i<range;i++){
			input.reset();
			input = i;	

			// test CPU_1
			gettimeofday (Tps, Tzp);
			auto output = p_pipeline<ConditionalPinning<1>>(input,t4,t3,t2,t1);

			output.wait();

			double elapsed = computeElapsed();

			results_cpu1(0,i)+=elapsed;

			// test CPU_2
			input.reset();
			gettimeofday (Tps, Tzp);
			output = p_pipeline<ConditionalPinning<2>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = computeElapsed();
			results_cpu2(0,i)+=(elapsed);

			// test CPU_3
			input.reset();
			gettimeofday (Tps, Tzp);
			output = p_pipeline<ConditionalPinning<3>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = computeElapsed();
			results_cpu3(0,i)+=(elapsed);

			// test CPU_4
			input.reset();
			gettimeofday (Tps, Tzp);
			output = p_pipeline<ConditionalPinning<4>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = computeElapsed();
			results_cpu4(0,i)+=(elapsed);


			// Serial Implementation
			auto data_v = input.getData();
			auto output_v = std::vector<int>();		

			gettimeofday (Tps, Tzp);
			pipeline(data_v,std::back_inserter(output_v),t4,t3,t2,t1);
			gettimeofday (Tpf, Tzp);

			elapsed = computeElapsed();
			serial_results(0,i)+=elapsed;


			std::cout << "ite " << j << " test " << i << "\n";
		}
		
	}

	
	{ 
		std::ofstream fstream = std::ofstream("parallel_test");
		fstream << "results_cpu1 = [ " << results_cpu1/repteitions << "];\n";
		fstream << "results_cpu2 = [ " << results_cpu2/repteitions << "];\n";
		fstream << "results_cpu3 = [ " << results_cpu3/repteitions << "];\n";
		fstream << "results_cpu4 = [ " << results_cpu4/repteitions << "];\n";
		fstream << "serial_results = [ " << serial_results/repteitions << "];\n";
	}

	

}



