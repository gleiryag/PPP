#include<pipetest.hpp>

constexpr int w = 500;

int t1(int t){ dowork(w); return t+1; }
int t2(int t){ dowork(w); return t*2; }
int t3(int t){ dowork(w); return t*2; }
int t4(int t){ dowork(w); return t+5; }







using Row = Eigen::Matrix<double,1,Eigen::Dynamic>;

int main(int argc, char* argv[]){

	Timer& timer = Timer::getTimer();

	po::variables_map vm;
	
	initializeArgumentMap(argc,argv,vm);


	int range = vm.count("range") ? vm["range"].as<int>() : 100 ;
	int repetitions =  vm.count("repetitions") ? vm["repetitions"].as<int>() :   1;
	std::string filename = vm.count("filename") ? vm["filename"].as<std::string>() :   "parallel_test" ;


	std::cout << "Running test with range=" << range << " repetitions= " << repetitions << "\n";


	Row results_cpu1=Eigen::VectorXd::Zero(range);

	for(int j =0;j<repetitions;j++){

		Source<int> input(true);

		for(int i=0;i<range;i++){
			input.reset();
			input = i;	

			// test CPU_1
			timer.set();
			auto output = p_pipeline<PINNING_STRATEGY>(input,t4,t3,t2,t1);

			output.wait();

			double elapsed = timer.computeElapsed();

			results_cpu1(0,i)+=elapsed;

		}
		
	}

	
	{ 
		std::ofstream fstream = std::ofstream(filename);
		fstream << "results_cpu1 = [ " << results_cpu1/repetitions << "];\n";

	}

	

}



