all: q1 q1-chain q1-optimise q2 q2-chain

q1: q1.o
	g++ q1.o -o q1

q1-chain: q1-chain.o
	g++ q1-chain.o -o q1-chain

q1-optimise: q1-optimise.o
	g++ q1-optimise.o -o q1-optimise

q2: q2.o
	g++ q2.o -o q2

q2-chain: q2-chain.o
	g++ q2-chain.o -o q2-chain

q1-optimise.o: q1-optimise.cpp
	g++ -c q1-optimise.cpp

q1-chain.o: q1-chain.cpp
	g++ -c q1-chain.cpp

q1.o: q1.cpp
	g++ -c q1.cpp

q2.o: q2.cpp
	g++ -c q2.cpp

q2-chain.o: q2-chain.cpp
	g++ -c q2-chain.cpp

clean:
	rm *.o q1 q1-chain q1-optimise q2 q2-chain
