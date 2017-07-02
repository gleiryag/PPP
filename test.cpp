#include<Test.hpp>
#include<sstream>
#include<iostream>



int main(){


	Test test(std::vector<int>{1,1},10,1,std::vector<int>{1},PipeModifier(true) );


	test.build();


}
