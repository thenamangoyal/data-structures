all: q1 q1-fast q2 q2-fast

q1: q1.o
	g++ q1.o -o q1

q1-fast: q1-fast.o
	g++ q1-fast.o -o q1-fast

q2: q2.o
	g++ q2.o -o q2

q2-fast: q2-fast.o
	g++ q2-fast.o -o q2-fast

q1.o: q1.cpp
	g++ -c q1.cpp

q1-fast.o: q1-fast.cpp
	g++ -c q1-fast.cpp

q2.o: q2.cpp
	g++ -c q2.cpp

q2-fast.o: q2-fast.cpp
	g++ -c q2-fast.cpp

clean:
	rm *.o q1 q1-fast q2 q2-fast
