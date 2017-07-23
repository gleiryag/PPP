#include<mainutils.hpp>



using INT_1 = struct { int array[1]; };
INT_1 stage_0( INT_1 input){ dowork(10) ; return input; }
INT_1 stage_1( INT_1 input){ dowork(10) ; return input; }
INT_1 stage_2( INT_1 input){ dowork(10) ; return input; }
INT_1 stage_3( INT_1 input){ dowork(10) ; return input; }
INT_1 stage_4( INT_1 input){ dowork(10) ; return input; }



int main(){
	INT_1 value = { 0};
	std::vector<Row> results{};
	Timer& timer = Timer::getTimer();
	for(int i ; i < 5 ; i++){
		Source<INT_1> input(true);
		Row exp_results=Eigen::VectorXd::Zero(10);

		for(int j = 0 ; j < 10 ; j++){
			input.getData().push_back(value);
			timer.set();
			auto output = k_pipeline<3,ConditionalPinning<2>>(input,stage_0,stage_1,stage_2,stage_3,stage_4);
			output.wait();
			double elapsed = timer.computeElapsed();
			exp_results(0,j)=elapsed;
		}
		results.push_back(exp_results);
	}
	process_results("test_5_1_1_1_1_1_k_pipeline_3_ConditionalPinning_2_",results);
}
