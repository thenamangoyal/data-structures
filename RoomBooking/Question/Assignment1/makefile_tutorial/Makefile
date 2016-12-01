all: sample

sample: main.o factorial.o hello.o add.o
	g++ main.o factorial.o hello.o add.o -o sample

main.o: main.cpp
	g++ -c main.cpp

factorial.o: factorial.cpp
	g++ -c factorial.cpp

add.o: add.cpp
	g++ -c add.cpp

hello.o: hello.cpp
	g++ -c hello.cpp



clean:
	rm *o sample
