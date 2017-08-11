#pragma once
#include<initializer_list>
#include<pthread.h>
#include<utility>
#include<memory>
#include<iostream>


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
		
		if(*is_stream_closed_ptr && *current_ptr==data().size()) throw new std::out_of_range("Out of range: stream is already closed"); //fix?
		return;
	}


	public :


		Source(Source<T> const & source){
			*this = source;
		}

		Source(bool closed)  {  

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
			
			*is_stream_closed_ptr = closed;
			*current_ptr = 0;
			if( pthread_cond_init(cond_ptr.get(),NULL)) throw  std::exception();
			if( pthread_mutex_init(mutex_ptr.get(),NULL)) throw  std::exception(); }

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


			return *this;

		}

		void end_stream(){

			pthread_mutex_lock(mutex_ptr.get());

			*is_stream_closed_ptr = true;

			pthread_cond_broadcast(cond_ptr.get());
			pthread_mutex_unlock(mutex_ptr.get());
		}

		bool is_stream_done(){

			return *is_stream_closed_ptr &&  *current_ptr==data().size();//fix

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

		void append(const T& value,int n){

			for(int i =0; i < n ; i++){
				operator=(value);
			}
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
			wait();
			*current_ptr = 0;
		}

};
