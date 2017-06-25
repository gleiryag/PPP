#pragma once
#include<sys/time.h>
#include<memory>


class Timer {

	static Timer* timer;
	std::unique_ptr<struct timeval> Tps,Tpf;

	public :

	double computeElapsed(){

	 return ((Tpf->tv_sec-Tps->tv_sec)*1000000 + Tpf->tv_usec-Tps->tv_usec)/ (double)1000000;

	}

	void set(){

		gettimeofday (Tps.get(),0);
	}

	void stop(){

		gettimeofday (Tpf.get(), 0);
	}




	static Timer& getTimer(){
		if(timer==nullptr) timer= new Timer();
		return *timer;
	}


	private :
	

	Timer(){
		Tps.reset( new struct timeval);
		Tpf.reset( new struct timeval);

	}










};

