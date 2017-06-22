#include<vector>
#include<iterator>
#include<utility>
#include<type_traits>
#include"metatemplates.hpp"
#include<pthread.h>
#include<memory>
#include<iostream>
#include<initializer_list>
#include <sys/time.h>
#include <sched.h>

struct timeval *Tps,*Tpf;
struct timezone *Tzp;

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
check_function_pack_t<void, Functions...> pipeline(InputContainer c,std::back_insert_iterator<OutputContainer>  it,Functions... params){


	for(auto& x : c){
		it = callF(x,params...);
	}
	return;
}


/////////////////////////////////////////////// Parallel implementation


struct pthread_cond_deleter{

	void operator()(pthread_cond_t* ptr){

		if(ptr!=nullptr){
			pthread_cond_destroy(ptr);
		}

	}



};

struct pthread_mutex_deleter{


	


	void operator()(pthread_mutex_t* ptr){
		if(ptr!=nullptr){
			pthread_mutex_destroy(ptr);
		}

	}



};



template<typename T>
class Source {

	using Container = std::vector<T>;
	using iterator = size_t;

	std::shared_ptr<Container> data_ptr;
	std::shared_ptr<pthread_cond_t> cond_ptr;
	std::shared_ptr<pthread_mutex_t> mutex_ptr;
	std::shared_ptr<bool> is_stream_closed_ptr;
	std::shared_ptr<iterator> current_ptr;

	Container& data(){

		return *data_ptr;

	}

	void waitPush(){ 


		pthread_mutex_lock(mutex_ptr.get());
		
		while(!*is_stream_closed_ptr && *current_ptr==data().size() ) pthread_cond_wait(cond_ptr.get(), mutex_ptr.get());
		pthread_mutex_unlock(mutex_ptr.get());
		
		if(*is_stream_closed_ptr && *current_ptr==data().size()) throw new std::out_of_range("Out of range: stream is already closed");
		return;
	}

	public :


		Source(Source<T> const & source){
			
			*this = source;
		}

		Source(bool closed) : Source() {  *is_stream_closed_ptr = closed; }

		Source(std::initializer_list<T> initializer){

			auto container = new Container(initializer);
			auto cond = new pthread_cond_t; 	
			auto mutex = new pthread_mutex_t;
			auto is_stream_closed = new bool;
			auto current = new iterator;
			
			
			data_ptr.reset(container);
			cond_ptr.reset(cond,pthread_cond_deleter{});
			mutex_ptr.reset( mutex ,pthread_mutex_deleter{});
			is_stream_closed_ptr.reset(is_stream_closed);
			current_ptr.reset(current);
			
			*is_stream_closed_ptr = true;
			*current_ptr = 0;
			if( pthread_cond_init(cond_ptr.get(),NULL)) throw  std::exception();
			if( pthread_mutex_init(mutex_ptr.get(),NULL)) throw  std::exception();
			

		}

		Source(){

			auto container = new Container();
			auto cond = new pthread_cond_t; 	
			auto mutex = new pthread_mutex_t;
			auto is_stream_closed = new bool;
			auto current = new iterator;
			
			
			data_ptr.reset(container);
			cond_ptr.reset(cond,pthread_cond_deleter{});
			mutex_ptr.reset( mutex ,pthread_mutex_deleter{});
			is_stream_closed_ptr.reset(is_stream_closed);
			current_ptr.reset(current);
			
			*is_stream_closed_ptr = false;
			*current_ptr = 0;

			if( pthread_cond_init(cond_ptr.get(),NULL)) throw  std::exception();
			if( pthread_mutex_init(mutex_ptr.get(),NULL)) throw  std::exception();

		}

		Source<T>& operator=(Source<T> const& source){

			data_ptr = source.data_ptr;
			cond_ptr = source.cond_ptr;
			mutex_ptr = source.mutex_ptr;
			is_stream_closed_ptr = source.is_stream_closed_ptr;
			current_ptr = source.current_ptr;


		}

		void end_stream(){

			pthread_mutex_lock(mutex_ptr.get());

			*is_stream_closed_ptr = true;

			pthread_cond_broadcast(cond_ptr.get());
			pthread_mutex_unlock(mutex_ptr.get());
		}

		bool is_stream_done(){

			return *is_stream_closed_ptr &&  *current_ptr==data().size();

		}


		void wait(){


			pthread_mutex_lock(mutex_ptr.get());
			while(!*is_stream_closed_ptr ) pthread_cond_wait(cond_ptr.get(), mutex_ptr.get());
			pthread_mutex_unlock(mutex_ptr.get());
			return;

		}


		Container getData() {
			wait();
			return data();

		}

		

		Source<T>& operator=(const T& value){

			pthread_mutex_lock(mutex_ptr.get());

			data().push_back(value);

			pthread_cond_broadcast(cond_ptr.get());
			pthread_mutex_unlock(mutex_ptr.get());
			return *this;

		}

		const T next(){
			
			waitPush();
			
			T next = data()[*current_ptr];

			*current_ptr += 1;
			
			return next;

		}

		std::ostream& print(std::ostream & os) const {
			std::cout << "data_ptr{";
			if(data_ptr.get()!=nullptr) for(auto x: *data_ptr.get()) std::cout <<  x << ",";

			return os << "} " << data_ptr.get() << " cond_ptr " <<
			cond_ptr.get() << " mutex_ptr " << mutex_ptr.get() << 
			" is_stream_ptr " << is_stream_closed_ptr.get() << " current_ptr " 
			<< current_ptr.get() << "]" ; 


		}

		void reset(){
			*current_ptr = 0;
		}


};

template<typename T>
std::ostream& operator<<(std::ostream& os,Source<T> const & s){
	return s.print(os);
}

struct DefaultPipeConfiguration {

	void thread_pinning_policy(pthread_t pthread,int id){

		return;
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


template<typename F,typename ConfigurationAlg = DefaultPipeConfiguration>
class ThreadHandler {

	using InputSource  = Source<input_t<F>>;
	using OutputSource = Source<return_t<F>>;

	F f;
	std::shared_ptr<pthread_t> thread_ptr;
	InputSource isource;
	OutputSource osource;
	ConfigurationAlg algorithms;
	int id;
	
	

	static void* static_run(void* class_t){ 

		ThreadHandler& handler = *(static_cast<ThreadHandler<F,ConfigurationAlg>*>(class_t));
		handler.run();
		delete &handler; 
		return 0;
		
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
		gettimeofday (Tpf, Tzp); 
	}

	


	public : 

	ThreadHandler(InputSource& source,F f,int i) { 

		this->f = f;
		isource=source;
		id = i;
		thread_ptr.reset(new pthread_t);
		algorithms.thread_pinning_policy(*thread_ptr,id);
		
	}

	

	OutputSource destroySource(){
		
		if(pthread_create(thread_ptr.get(), NULL,static_run,this)){
			throw new std::bad_alloc;
		}
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





