
/* 
get return and input types of type T, assuming T is a function pointer (reference) 
i.e RETURN_TYPE (*)(INPUT_TYPE) or RETURN_TYPE (&)(INPUT_TYPE)
*/

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

/*
Aliases for return and input types defined in function_types
*/

template<typename T>
using return_t = typename function_types<T>::return_t;

template<typename T>
using input_t =  typename function_types<T>::input_t;




template<bool b, typename T>
using enable_if_t = typename std::enable_if<b,T>::type;

// Logic functions


template<bool A, bool B >
struct conjunction {
	static constexpr bool value = true;
};

template<>
struct conjunction<false,false>{
	static constexpr bool value = false ;
};


template<bool A, bool B >
struct disjunction {
	static constexpr bool value = false;
};

template<>
struct disjunction<true,true>{
	static constexpr bool value = true ;
};


template<typename T>
struct has_type { using type = T; };



template<typename T,typename... Tail>
struct unfold_return : has_type<return_t<T>> {  };


/*
 Types... function pointers type's pack
return the return type of the first function pointer
*/
template<typename... Types>
using unfold_return_t= typename unfold_return<Types...>::type;
/*
 Types... function pointers type's pack
return the return type of the last function pointer
*/
template<typename... P0toPN>
struct unfold_input;

template<typename PN>
struct unfold_input<PN> : has_type<input_t<PN>> {};

template<typename P0,typename P1,typename... P2toPN>
struct unfold_input<P0,P1,P2toPN...> : unfold_input<P1,P2toPN...> {};

template<typename... P0toPN>
using unfold_input_t = typename unfold_input<P0toPN...>::type;

/* 
Input: A, B are function pointers
- check if the call to A provides the same type as the input to B
*/

template<typename A, typename B>
static constexpr bool is_function_type_consistent = std::is_same<input_t<A>,return_t<B>>::value;

template<typename... Args>
struct check_function_pack;


template<typename T, typename U,typename... Args>
struct check_function_pack<T,U,Args...>{

	static constexpr bool value = is_function_type_consistent<T,U> && check_function_pack<U,Args...>::value;

};

template<typename T>
struct check_function_pack<T>{

	static constexpr bool value = true;

};


template<typename T, typename... Args>
using  check_function_pack_t = typename std::enable_if<check_function_pack<Args...>::value,T>::type ;


