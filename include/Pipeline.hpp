#pragma once
#include<vector>
#include<iterator>
#include<Source.hpp>
#include<metatemplates.hpp>
#include<pthread.h>
#include<iostream>
#include<Timer.hpp>
#include<PipeConfiguration.hpp>


/*
 F - is a function pointer.
 Val - is an input value to F.
calls F supplying the value val to it.
*/
template<typename Val,typename F>
unfold_return_t<F> callF(Val value,F f){
	return f(value);
}

/*
 F - is a function pointer.
 Val - is an input value to F.
 Types... - remaining pointer functions
calls functions types in a pack with leftmost precedence. 
*/

template<typename Val,typename F,typename... Functions>
unfold_return_t<Functions...> callF(Val val, F f,Functions... functions){
	return f(callF(val,functions...));
}





template<typename InputContainer,typename OutputContainer,typename... Functions>
void pipeline(InputContainer c,std::back_insert_iterator<OutputContainer>  it,Functions... params){
	for(auto& x : c){
		it = callF(x,params...);
	}
	return;
}


/////////////////////////////////////////////// Parallel implementation

template<typename F,typename ConfigurationAlg = DefaultPipeConfiguration>
class ThreadHandler {

	using InputSource  = Source<input_t<F>>;
	using OutputSource = Source<return_t<F>>;

	F f;
	InputSource isource;
	OutputSource osource;
	ConfigurationAlg algorithms;
	int id;
	std::shared_ptr<pthread_t> thread_ptr;
	
	static void* static_run(void* class_t){ 

		ThreadHandler& handler = *(static_cast<ThreadHandler<F,ConfigurationAlg>*>(class_t));
		handler.run();

		delete &handler; 
		Timer::getTimer().stop(); 
		pthread_exit(0);
		
	}

	void run(){

		while(!isource.is_stream_done()){

			try {

				input_t<F> in = isource.next();
				osource = f(in);

			}catch(std::out_of_range* e){
				break;
			}

		}

		osource.end_stream();
		
	}

	public : 

	ThreadHandler(InputSource& source,F func,int i) : f{func} { 

		isource=source;
		id = i;
		thread_ptr.reset(new pthread_t);
		algorithms.thread_pinning_policy(*thread_ptr,id);
		
	}

	

	OutputSource destroySource(){
		
		if(int status = pthread_create(thread_ptr.get(), NULL,static_run,this)){
			throw new std::exception();
		}

		algorithms.thread_detach_policy(*thread_ptr,id);
		return osource;	
	}

	std::ostream& print(std::ostream & os) const {
			return os  << "ISOURCE-" << isource << " OSOURCE-" << osource << " ID " << thread_ptr.get() ; 
		}


};

template<typename T>
std::ostream& operator<<(std::ostream& os,ThreadHandler<T> const & s){
	return s.print(os);
}

/*
 F - is a function pointer.
 Val - is an input value to F.
calls F supplying the value val to it.
*/
template<typename ConfigurationAlg = DefaultPipeConfiguration, typename F>
Source<return_t<F>> parallel_call(int id,Source<input_t<F>>& input,F f){

	auto handler = new ThreadHandler<F,ConfigurationAlg>(input,f,id);

	return handler->destroySource();

}

/*
 F - is a function pointer.
 Val - is an input value to F.
 Types... - remaining pointer functions
calls functions types in a pack with leftmost precedence. 
*/

template<typename ConfigurationAlg = DefaultPipeConfiguration,typename F,typename... Functions>
Source<return_t<F>> parallel_call(int id,Source<unfold_input_t<Functions...>>& input,F f,Functions... remain_functions_ptrs){
	
	auto pipe_output = parallel_call<ConfigurationAlg>(id+1,input,remain_functions_ptrs...);

	auto handler = new ThreadHandler<F,ConfigurationAlg>(pipe_output,f,id);
	
	return handler->destroySource();

}



template<typename ConfigurationAlg = DefaultPipeConfiguration,typename... Functions>
check_function_pack_t<Source<unfold_return_t<Functions...>>, Functions...> p_pipeline(Source<unfold_input_t<Functions...>>& input,Functions... functions_ptrs){
	return parallel_call<ConfigurationAlg>(0,input,functions_ptrs...);


}








#include<functioncomposition.hpp>



template<size_t INDEX,size_t K,typename ConfigurationAlg = DefaultPipeConfiguration,typename... Functions>
auto k_parallel_call(std::enable_if_t<(INDEX+1)*K>=sizeof...(Functions),int> id,Source<unfold_input_t<Functions...>>& input,FunctionSequence<Functions...>& functions){

	
	constexpr size_t INIT_INDEX = INDEX*K;
	constexpr size_t FINAL_INDEX = sizeof...(Functions)-1;	
	auto f = functions. template stage<INIT_INDEX,FINAL_INDEX>();


	auto handler = new ThreadHandler<decltype(f),ConfigurationAlg>(input,f,id);
	return handler->destroySource();

	
}




template<size_t INDEX,size_t K,typename ConfigurationAlg = DefaultPipeConfiguration,typename... Functions>
auto k_parallel_call(std::enable_if_t<(INDEX+1)*K<sizeof...(Functions),int> id,Source<unfold_input_t<Functions...>>& input,FunctionSequence<Functions...> functions){

	constexpr size_t INIT_INDEX = INDEX*K;
	constexpr size_t FINAL_INDEX = (INDEX+1)*K-1;	


	auto f = functions.template stage<INIT_INDEX,FINAL_INDEX>();

	auto pipe_output = k_parallel_call<INDEX+1,K,ConfigurationAlg>(id+1,input,functions);

	auto handler = new ThreadHandler<decltype(f),ConfigurationAlg>(pipe_output,f,id);
	
	return handler->destroySource();

}





template<size_t K,typename ConfigurationAlg = DefaultPipeConfiguration,typename... Functions>
auto k_pipeline(Source<unfold_input_t<Functions...>>& input,Functions... functions_ptrs){
	auto f_sequence = make_sequence(functions_ptrs...); 
	return k_parallel_call<0,K,ConfigurationAlg>(0,input,f_sequence);
}

