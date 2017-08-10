CXX=g++
CPPVERSION = c++11
SRCDIR = ./src
INCLUDEDIR = ./include
LIBDIR = ./lib
CPPFLAGS= -g -std=$(CPPVERSION)
CXXFLAGS= -I $(INCLUDEDIR) 


LIBDIR = ./lib
LINK = -lpthread

TEST_NAME = default_testname
 
test : main.cpp mainutils.o timer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) mainutils.o timer.o $(LIBDIR)/libboost_program_options.a main.cpp  -o test.o -L $(LIBDIR) $(LINK) 


$(TEST_NAME) : pipetest.cpp timer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) timer.o $(LIBDIR)/libboost_program_options.a pipetest.cpp  -o $(TEST_NAME) -L $(LIBDIR) $(LINK) 

test-gen: test.cpp 
	rm test_source/*
	g++ -I include/ -L lib/ Test_w10.cpp -o Test_w10
	g++ -I include/ -L lib/ Test_w100.cpp -o Test_w100
	g++ -I include/ -L lib/ Test_w250.cpp -o Test_w250
	g++ -I include/ -L lib/ Test_w500.cpp -o Test_w500
	./Test_w10
	./Test_w100
	./Test_w250
	./Test_w500
	
all: test $(TEST_NAME)
	rm *.o
clean:
	rm *.o
