
all: main.o
	g++ -std=c++11 main.cpp -o main.o -pthread

clean:
	rm -rf main.o
