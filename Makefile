all: main

main: main.o visitor.o
	g++ main.o visitor.o -o main.bin

main.o: main.cpp
	g++ -c main.cpp -o main.o

visitor.o: visitor.cpp
	g++ -c visitor.cpp -o visitor.o
