all: main

main: main.o Graph.h
	g++ main.o -o main

main.o: main.cpp Graph.h
	g++ -c main.cpp

clean:
	rm -f *.o main
