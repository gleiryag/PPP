#pragma once
#include<type_traits>
#include<Source.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os,Source<T> const & s){
	return s.print(os);
}

struct DefaultPipeConfiguration {

	void thread_pinning_policy(pthread_t pthread,int id){
		return;
	}
	
	void thread_detach_policy(pthread_t pthread,int id){

		pthread_detach(pthread);
	}


};


template<int N>
struct ConditionalPinning : DefaultPipeConfiguration {
	
	void thread_pinning_policy(pthread_t pthread,int id){
		static_assert(N>0,"N must be positive non-zero number");
		int cpu_assignment = id%N;
		cpu_set_t set;
		
		CPU_ZERO(&set);
		CPU_SET(cpu_assignment,&set);	
		pthread_setaffinity_np(pthread,sizeof(cpu_set_t),&set);
		
		return;
	}
};