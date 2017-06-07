#include<vector>
#include<iterator>
#include<type_traits>


template<typename T>
struct function_types{

	using return_t =  void;
	using input_t =  void;
};

template<typename T,typename R>
struct function_types<R(*)(T)> {

	using return_t =  R;
	using input_t =  T;
	
};

template<typename T,typename R>
struct function_types<R(&)(T)> {

	using return_t =  R;
	using input_t =  T;
	
};



template<typename T>
using return_t = typename function_types<T>::return_t;

template<typename T>
using input_t =  typename function_types<T>::input_t;

template<bool b, typename T>
using enable_if_t = typename std::enable_if<b,T>::type;
 
template<typename A, typename B>
static constexpr bool is_function_type_consistent = std::is_same<return_t<A>,input_t<B>>::value;

template<typename A,typename B,typename C>
using is_function_type_consistent_t =  enable_if_t<is_function_type_consistent<A,B>,C> ; 

//template<typename Container,typename T>
//using check_container_type =  enable_if_t<std::is_same<typename Container::value_type,T>::value,Container>;




//template<typename InputContainer, typename A>
//using input_container_type = typename check_container_type<InputContainer,input_t<A>>::type ;

//template<typename OutputContainer, typename A>
//using output_stream_type = typename pb_it<check_container_type<OutputContainer,return_t<A>>>::type ;

template<typename A, typename B,typename InputContainer,typename OutputContainer>
is_function_type_consistent_t<A,B,void> simple_pipeline(A f,B g,InputContainer c,std::back_insert_iterator<OutputContainer>  it){
	for(auto& x : c){
		it = g(f(x));
	}
	return;
}
