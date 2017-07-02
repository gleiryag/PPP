#include<mainutils.hpp>
#include<Eigen/Dense>
#include<Timer.hpp>



using Row = Eigen::Matrix<double,1,Eigen::Dynamic>;
using INT_1 = struct { int array[1]; };
INT_1 stage_0( INT_1 input){ dowork(50) ; return input; }



int main(){
	INT_1 value = { 0};
	std::vector<Row> results{};
	Timer& timer = Timer::getTimer();
	for(int i ; i < 100 ; i++){
		Source<INT_1> input(true);
		Row exp_results=Eigen::VectorXd::Zero(10);

		for(int j = 0 ; j < 10 ; j++){
			input.getData().push_back(value);
			timer.set();
			auto output = p_pipeline(input,stage_0);
			output.wait();
			double elapsed = timer.computeElapsed();
			exp_results(0,j)=elapsed;
		}
		results.push_back(exp_results);
	}
}

