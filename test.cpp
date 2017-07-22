#include<Test/Test.hpp>
#include<sstream>
#include<iostream>



int main(){

	// Simple pipe test 
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(false) ); test.build(); }
	
	//Parallel pipe with no pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true) ); test.build(); }
	
	// Parallel pipe with mod pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"ConditionalPinning<5>") ); test.build(); }
	
	//Parallel Pipe with SerialPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"SerialPinning<5>") ); test.build(); }
	
	// Parallel pipe with merging no pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,""); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,""); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,""); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,""); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,""); test.build(); }
	
	// Parallel pipe with merging Serial pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<5>") ); test.build(); }
	
	// Parallel pipe with merging ConditionalPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"ConditionalPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"ConditionalPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"ConditionalPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"ConditionalPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"ConditionalPinning<1>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"ConditionalPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"ConditionalPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"ConditionalPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"ConditionalPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"ConditionalPinning<2>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"ConditionalPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"ConditionalPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"ConditionalPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"ConditionalPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"ConditionalPinning<3>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"ConditionalPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"ConditionalPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"ConditionalPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"ConditionalPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"ConditionalPinning<4>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"ConditionalPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"ConditionalPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"ConditionalPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"ConditionalPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"ConditionalPinning<5>") ); test.build(); }

	// Parallel pipe with merging SerialPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<1>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<2>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<3>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<4>") ); test.build(); }
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"SerialPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"SerialPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"SerialPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"SerialPinning<5>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"SerialPinning<5>") ); test.build(); }
	
	
	// Parallel Pipe with CPU Limit 
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,"CPU_Limit<5>") ); test.build(); }
	
	// Parallel pipe with merging  and CPU Limit

	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,1,"CPU_Limit<1>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,2,"CPU_Limit<2>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,3,"CPU_Limit<3>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,4,"CPU_Limit<4>") ); test.build(); }
	{ Test test(std::vector<int>{1,1,1,1,1,1},10,5,std::vector<int>{10,10,10,10,10},PipeModifier(true,5,"CPU_Limit<5>") ); test.build(); }

}
