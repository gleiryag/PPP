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
	rm -f test_source/*
	g++ -I include/ -L lib/ Test_w2.cpp -o Test_w2
	./Test_w2
	echo "w2 compiled"
	g++ -I include/ -L lib/ Test_w6.cpp -o Test_w6
	./Test_w6
	echo "w6 compiled"
	g++ -I include/ -L lib/ Test_w10.cpp -o Test_w10
	./Test_w10
	echo "w10 compiled"
	g++ -I include/ -L lib/ Test_w10.cpp -o Test_w100
	./Test_w100
	echo "w100 compiled"
all: test $(TEST_NAME)
	rm *.o
clean:
	rm *.o
