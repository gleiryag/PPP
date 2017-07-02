#include<mainutils.hpp>
#include <Eigen/Dense>
#include<Timer.hpp>

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


	std::cout << "Running test with range=" << range << " repetitions= " << repetitions << "\n";


	Row results_cpu1=Eigen::VectorXd::Zero(range);
	Row results_cpu2=Eigen::VectorXd::Zero(range);
	Row results_cpu3=Eigen::VectorXd::Zero(range);
	Row results_cpu4=Eigen::VectorXd::Zero(range);
	Row serial_results=Eigen::VectorXd::Zero(range);

	for(int j =0;j<repetitions;j++){

		Source<int> input(true);

		for(int i=0;i<range;i++){
			input.reset();
			input = i;	

			// test CPU_1
			timer.set();
			auto output = p_pipeline<ConditionalPinning<1>>(input,t4,t3,t2,t1);

			output.wait();

			double elapsed = timer.computeElapsed();

			results_cpu1(0,i)+=elapsed;

			// test CPU_2
			input.reset();
			timer.set();
			output = p_pipeline<ConditionalPinning<2>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = timer.computeElapsed();
			results_cpu2(0,i)+=(elapsed);

			// test CPU_3
			input.reset();
			timer.set();
			output = p_pipeline<ConditionalPinning<3>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = timer.computeElapsed();
			results_cpu3(0,i)+=(elapsed);

			// test CPU_4
			input.reset();
			timer.set();
			output = p_pipeline<ConditionalPinning<4>>(input,t4,t3,t2,t1);

			output.wait();

			elapsed = timer.computeElapsed();
			results_cpu4(0,i)+=(elapsed);


			// Serial Implementation
			auto data_v = input.getData();
			auto output_v = std::vector<int>();		

			timer.set();
			pipeline(data_v,std::back_inserter(output_v),t4,t3,t2,t1);
			timer.stop();

			elapsed = timer.computeElapsed();
			serial_results(0,i)+=elapsed;


			std::cout << "ite " << j << " test " << i << "\n";
		}
		
	}

	
	{ 
		std::ofstream fstream = std::ofstream("parallel_test");
		fstream << "results_cpu1 = [ " << results_cpu1/repetitions << "];\n";
		fstream << "results_cpu2 = [ " << results_cpu2/repetitions << "];\n";
		fstream << "results_cpu3 = [ " << results_cpu3/repetitions << "];\n";
		fstream << "results_cpu4 = [ " << results_cpu4/repetitions << "];\n";
		fstream << "serial_results = [ " << serial_results/repetitions << "];\n";
	}

	

}



