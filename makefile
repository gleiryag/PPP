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


all: test $(TEST_NAME)
	rm *.o
clean:
	rm *.o
