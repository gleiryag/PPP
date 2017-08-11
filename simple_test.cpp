#include<mainutils.hpp>

constexpr int w = 500;

int t1(int t){ dowork(w); return t+1; }
int t2(int t){ dowork(w); return t*2; }
int t3(int t){ dowork(w); return t*2; }
int t4(int t){ dowork(w); return t+5; }


int main(int argc, char* argv[]){

	Timer& timer = Timer::getTimer();
	double elapsed; 

	timer.set();
	t4(500);
	timer.stop();

	elapsed = timer.computeElapsed();
	std::cout << "work time " << elapsed  << "\n";

	Source<int> input{1,2,3,4,5,6,7,8,9,10};

	timer.set();
	auto output = p_pipeline(input,t4,t3,t2,t1);

	output.wait();
	elapsed = timer.computeElapsed();
	

	std::cout << "time " << elapsed << output << "\n";

	auto output_v = std::vector<int>();	

	timer.set();
	pipeline(input.getData(),std::back_inserter(output_v),t4,t3,t2,t1);
	timer.stop();

	elapsed = timer.computeElapsed();
	std::cout << "time " << elapsed  << "\n";
	

}



