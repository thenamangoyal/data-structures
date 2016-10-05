all: q1 q1-chain q1-extra q2 q2-chain q2-extra

q1: q1.o
	g++ q1.o -o q1

q1-chain: q1-chain.o
	g++ q1-chain.o -o q1-chain

q1-extra: q1-extra.o
	g++ q1-extra.o -o q1-extra

q2: q2.o
	g++ q2.o -o q2

q2-chain: q2-chain.o
	g++ q2-chain.o -o q2-chain

q2-extra: q2-extra.o
	g++ q2-extra.o -o q2-extra

q1.o: q1.cpp
	g++ -c q1.cpp

q1-chain.o: q1-chain.cpp
	g++ -c q1-chain.cpp

q1-extra.o: q1-extra.cpp
	g++ -c q1-extra.cpp

q2.o: q2.cpp
	g++ -c q2.cpp

q2-chain.o: q2-chain.cpp
	g++ -c q2-chain.cpp

q2-extra.o: q2-extra.cpp
	g++ -c q2-extra.cpp

clean:
	rm *.o q1 q1-chain q1-extra q2 q2-chain q2-extra
