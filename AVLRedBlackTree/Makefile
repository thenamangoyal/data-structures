all: q1 q2 q3

q1: q1.o
	g++ q1.o -o q1

q2: q2.o
	g++ q2.o -o q2

q3: q3.o
	g++ q3.o -o q3

q1.o: q1.cpp Avl.h
	g++ -c q1.cpp

q2.o: q2.cpp Avl.h
	g++ -c q2.cpp

q3.o: q3.cpp RB.h
	g++ -c q3.cpp

clean:
	rm *.o q1 q2 q3
