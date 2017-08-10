#include<mainutils.hpp>



using INT_1 = struct { int array[1]; };
INT_1 stage_0( INT_1 input){ dowork(50) ; return input; }
INT_1 stage_1( INT_1 input){ dowork(50) ; return input; }
INT_1 stage_2( INT_1 input){ dowork(50) ; return input; }
INT_1 stage_3( INT_1 input){ dowork(50) ; return input; }
INT_1 stage_4( INT_1 input){ dowork(50) ; return input; }



int main(){
	INT_1 value = { 0};
	std::vector<Row> results{};
	Timer& timer = Timer::getTimer();
	for(int i =0 ; i < 20 ; i++){
		Source<INT_1> input(true);
		Row exp_results=Eigen::VectorXd::Zero(40);

		for(int j = 0 ; j < 40 ; j++){
			input=value;
			input.reset();
			timer.set();
			auto output = k_pipeline<4,SerialPinning<2>>(input,stage_0,stage_1,stage_2,stage_3,stage_4);
			output.wait();
			double elapsed = timer.computeElapsed();
			exp_results(0,j)=elapsed;
		}
		results.push_back(exp_results);
	}
	process_results("test_5__i20_s40_1_1_1_1_1_k_pipeline_4_SerialPinning_2_",results);
}
