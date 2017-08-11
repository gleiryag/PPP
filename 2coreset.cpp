#include<Test/Test.hpp>
#include<iostream>

int main(){
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread  - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(1,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(2,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(3,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(4,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(5,"ConditionalPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 1 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(1,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(2,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(3,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(4,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(5,"SerialPinning<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 1 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(1,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(2,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(3,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(4,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,10,std::vector<int>{10,10,10,10,10},PipeModifier(5,"CPU_Limit<2>") ); std::cout << test.get_name() << "\n"; } //#2 core - 1 thread - {NP}
}
