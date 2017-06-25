CXX=g++
CPPVERSION = c++11
SRCDIR = ./src
INCLUDEDIR = ./include
LIBDIR = ./lib
CPPFLAGS= -g -std=$(CPPVERSION)
CXXFLAGS= -I $(INCLUDEDIR) 


LIBDIR = ./lib
LINK = -lpthread 
test.o : main.cpp mainutils.o timer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) mainutils.o timer.o $(LIBDIR)/libboost_program_options.a main.cpp  -o test.o -L $(LIBDIR) $(LINK) 


all: test

clean:
	rm *.o
