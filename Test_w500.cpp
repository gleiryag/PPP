#include<Test/Test.hpp>
#include<sstream>
#include<iostream>

int main(){

	// Simple pipe test 
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(false) ); test.build(); } // #OS - 1 thread
	
	//Parallel pipe with no pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true) ); test.build(); } // #OS - 5 thread
	
	// Parallel pipe with mod pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"ConditionalPinning<1>") ); test.build(); } //#1 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"ConditionalPinning<2>") ); test.build(); } //#2 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"ConditionalPinning<3>") ); test.build(); } //#3 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"ConditionalPinning<4>") ); test.build(); } //#4 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"ConditionalPinning<5>") ); test.build(); } //#5 core - 5 thread - {RRP}
	
	//Parallel Pipe with SerialPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"SerialPinning<1>") ); test.build(); } //#1-core - 5 thread  - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"SerialPinning<2>") ); test.build(); } //#2 core - 5 thread  - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"SerialPinning<3>") ); test.build(); } //#3 core - 5 thread  - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"SerialPinning<4>") ); test.build(); } //#4 core - 5 thread  - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"SerialPinning<5>") ); test.build(); } //#5 core - 5 thread  - {SP}
	
	// Parallel pipe with merging no pinning
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"")); test.build(); } //#OS - 5 thread 
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"")); test.build(); } //#OS - 3 thread
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"")); test.build(); } //#OS - 2 thread
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"")); test.build(); } //#OS - 2 thread
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"")); test.build(); } //#OS - 1 thread
	
	
	// Parallel pipe with merging ConditionalPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"ConditionalPinning<1>") ); test.build(); } //#1 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"ConditionalPinning<1>") ); test.build(); } //#1 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"ConditionalPinning<1>") ); test.build(); } //#1 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"ConditionalPinning<1>") ); test.build(); } //#1 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"ConditionalPinning<1>") ); test.build(); } //#1 core - 1 thread - {RRP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"ConditionalPinning<2>") ); test.build(); } //#2 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"ConditionalPinning<2>") ); test.build(); } //#2 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"ConditionalPinning<2>") ); test.build(); } //#2 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"ConditionalPinning<2>") ); test.build(); } //#2 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"ConditionalPinning<2>") ); test.build(); } //#2 core - 1 thread - {RRP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"ConditionalPinning<3>") ); test.build(); } //#3 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"ConditionalPinning<3>") ); test.build(); } //#3 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"ConditionalPinning<3>") ); test.build(); } //#3 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"ConditionalPinning<3>") ); test.build(); } //#3 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"ConditionalPinning<3>") ); test.build(); } //#3 core - 1 thread - {RRP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"ConditionalPinning<4>") ); test.build(); } //#4 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"ConditionalPinning<4>") ); test.build(); } //#4 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"ConditionalPinning<4>") ); test.build(); } //#4 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"ConditionalPinning<4>") ); test.build(); } //#4 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"ConditionalPinning<4>") ); test.build(); } //#4 core - 1 thread - {RRP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"ConditionalPinning<5>") ); test.build(); } //#5 core - 5 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"ConditionalPinning<5>") ); test.build(); } //#5 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"ConditionalPinning<5>") ); test.build(); } //#5 core - 3 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"ConditionalPinning<5>") ); test.build(); } //#5 core - 2 thread - {RRP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"ConditionalPinning<5>") ); test.build(); } //#5 core - 1 thread - {RRP}

	// Parallel pipe with merging SerialPinning
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"SerialPinning<1>") ); test.build(); } //#1 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"SerialPinning<1>") ); test.build(); } //#1 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"SerialPinning<1>") ); test.build(); } //#1 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"SerialPinning<1>") ); test.build(); } //#1 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"SerialPinning<1>") ); test.build(); } //#1 core - 1 thread - {SP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"SerialPinning<2>") ); test.build(); } //#2 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"SerialPinning<2>") ); test.build(); } //#2 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"SerialPinning<2>") ); test.build(); } //#2 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"SerialPinning<2>") ); test.build(); } //#2 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"SerialPinning<2>") ); test.build(); } //#2 core - 1 thread - {SP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"SerialPinning<3>") ); test.build(); } //#3 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"SerialPinning<3>") ); test.build(); } //#3 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"SerialPinning<3>") ); test.build(); } //#3 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"SerialPinning<3>") ); test.build(); } //#3 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"SerialPinning<3>") ); test.build(); } //#3 core - 1 thread - {SP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"SerialPinning<4>") ); test.build(); } //#4 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"SerialPinning<4>") ); test.build(); } //#4 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"SerialPinning<4>") ); test.build(); } //#4 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"SerialPinning<4>") ); test.build(); } //#4 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"SerialPinning<4>") ); test.build(); } //#4 core - 1 thread - {SP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"SerialPinning<5>") ); test.build(); } //#5 core - 5 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"SerialPinning<5>") ); test.build(); } //#5 core - 3 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"SerialPinning<5>") ); test.build(); } //#5 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"SerialPinning<5>") ); test.build(); } //#5 core - 2 thread - {SP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"SerialPinning<5>") ); test.build(); } //#5 core - 1 thread - {SP}
	
	
	// Parallel Pipe with CPU Limit 
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"CPU_Limit<1>") ); test.build(); } //#1 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"CPU_Limit<2>") ); test.build(); } //#2 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"CPU_Limit<3>") ); test.build(); } //#3 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"CPU_Limit<4>") ); test.build(); } //#4 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(true,"CPU_Limit<5>") ); test.build(); } //#5 core - 5 thread - {NP}
	
	// Parallel pipe with merging  and CPU Limit
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"CPU_Limit<1>") ); test.build(); } //#1 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"CPU_Limit<1>") ); test.build(); } //#1 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"CPU_Limit<1>") ); test.build(); } //#1 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"CPU_Limit<1>") ); test.build(); } //#1 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"CPU_Limit<1>") ); test.build(); } //#1 core - 1 thread - {NP}
		
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"CPU_Limit<2>") ); test.build(); } //#2 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"CPU_Limit<2>") ); test.build(); } //#2 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"CPU_Limit<2>") ); test.build(); } //#2 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"CPU_Limit<2>") ); test.build(); } //#2 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"CPU_Limit<2>") ); test.build(); } //#2 core - 1 thread - {NP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"CPU_Limit<3>") ); test.build(); } //#3 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"CPU_Limit<3>") ); test.build(); } //#3 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"CPU_Limit<3>") ); test.build(); } //#3 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"CPU_Limit<3>") ); test.build(); } //#3 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"CPU_Limit<3>") ); test.build(); } //#3 core - 1 thread - {NP}
	
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"CPU_Limit<4>") ); test.build(); } //#4 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"CPU_Limit<4>") ); test.build(); } //#4 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"CPU_Limit<4>") ); test.build(); } //#4 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"CPU_Limit<4>") ); test.build(); } //#4 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"CPU_Limit<4>") ); test.build(); } //#4 core - 1 thread - {NP}

	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(1,"CPU_Limit<5>") ); test.build(); } //#5 core - 5 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(2,"CPU_Limit<5>") ); test.build(); } //#5 core - 3 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(3,"CPU_Limit<5>") ); test.build(); } //#5 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(4,"CPU_Limit<5>") ); test.build(); } //#5 core - 2 thread - {NP}
	{ Test test(std::vector<int>{1,1,1,1,1,1},5,20,100,std::vector<int>{500,500,500,500,500},PipeModifier(5,"CPU_Limit<5>") ); test.build(); } //#5 core - 1 thread - {NP}
}
