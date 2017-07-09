#pragma once

#include<array>
#include <boost/any.hpp>
#include<tuple>
#include<type_traits>


template<typename F>
return_t<F> function_composition(input_t<F> input, F f ){
		return f (input);
	}

template<typename F, typename... Functions>
return_t<F> function_composition(unfold_input_t<Functions...> input, F f , Functions... func ){

		
		return f(function_composition(input,func...));

	}


template<typename... Functions>
auto lambdacomposition(Functions... functions ) {
	return [functions...] ( unfold_input_t<Functions...> input ) { return function_composition(input,functions...);  };
}



template <typename... Functions>
class FunctionSequence{


	static const std::size_t size = sizeof...(Functions);
	std::array<boost::any,size> function_array;

	

/*
	template<size_t N>
	using return_t = typename return_t<type<N>>;
	template<size_t K>
	using input_t = typename input_t<type<K>>;

*/
	public :


	template<size_t INDEX >
	using type = typename std::tuple_element<INDEX,std::tuple<Functions...>>::type;

	template<size_t INDEX, size_t K>
	using source_type = return_t<type<INDEX*K>>;

	FunctionSequence(Functions... functors) {

		add(0,functors...);
	}

	template<typename F>
	void add(size_t index, F f){
		function_array[index] = f;
	}

	template<typename F,typename... Rest>
	void add(size_t index, F f,Rest... functions){
		function_array[index] = f;
		add(index+1,functions...);
	}

	template<size_t INDEX>
	auto stage(){

		return boost::any_cast<type<INDEX>>(function_array[INDEX]);

	}


	template<size_t N, size_t K,typename std::enable_if_t<N<K,int> = 0 >
	auto stage(){

		
		return lambdacomposition(stage<N>(),stage<N+1,K>());

	}

	template<size_t N, size_t K>
	std::enable_if_t<N==K,type<N>> stage(){

		
		return stage<N>();

	}

};


template<typename... Functions> 
FunctionSequence<Functions...> make_sequence(Functions... functors) {

	return FunctionSequence<Functions...>(functors...);
}





