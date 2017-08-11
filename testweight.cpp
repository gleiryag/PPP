#include<mainutils.hpp>


int main(){
	Timer& timer = Timer::getTimer();
	timer.set();
	dowork (10);
	timer.stop();
	double elapsed = timer.computeElapsed();

	std::cout << "work(10) time " << elapsed  << "\n";

	
	timer.set();
	dowork (100);
	timer.stop();
	elapsed = timer.computeElapsed();

	std::cout << "work(100) time " << elapsed  << "\n";


	timer.set();
	dowork (250);
	timer.stop();
	elapsed = timer.computeElapsed();

	std::cout << "work(250) time " << elapsed  << "\n";


	timer.set();
	dowork (500);
	timer.stop();
	elapsed = timer.computeElapsed();

	std::cout << "work(500) time " << elapsed  << "\n";

}
