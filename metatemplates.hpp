


template<bool A, bool B >
struct conjunction {
	static constexpr bool value = true;
};

template<bool B, typename A, typename B >
struct conjunction<false,false>{
	static constexpr bool value = false ;
};


template<bool A, bool B >
struct disjunction {
	static constexpr bool value = false;
};

template<bool B, typename A, typename B >
struct disjunction<true,true>{
	static constexpr bool value = true ;
};

