all: bs

bs: main.o ClassRoom.o ClassLab.o ClassLec.o FunctionsDataHandling.o FunctionsImplement.o FunctionsIO.o FunctionsTemplate.h
	g++ main.o ClassRoom.o ClassLab.o ClassLec.o FunctionsDataHandling.o FunctionsImplement.o FunctionsIO.o -o bs

main.o: main.cpp ClassRoom.h  ClassLab.h ClassLec.h FunctionsDataHandling.h FunctionsTemplate.h FunctionsImplement.h FunctionsIO.h
	g++ -c main.cpp

ClassRoom.o: ClassRoom.cpp ClassRoom.h
	g++ -c ClassRoom.cpp

ClassLab.o: ClassLab.cpp ClassLab.h ClassRoom.h
	g++ -c ClassLab.cpp

ClassLec.o: ClassLec.cpp ClassLec.h ClassRoom.h
	g++ -c ClassLec.cpp

FunctionsDataHandling.o: FunctionsDataHandling.cpp FunctionsDataHandling.h ClassRoom.h ClassLab.h ClassLec.h
	g++ -c FunctionsDataHandling.cpp

FunctionsImplement.o: FunctionsImplement.cpp FunctionsImplement.h ClassRoom.h ClassLab.h ClassLec.h FunctionsTemplate.h
	g++ -c FunctionsImplement.cpp

FunctionsIO.o: FunctionsIO.cpp FunctionsIO.h ClassRoom.h ClassLab.h ClassLec.h FunctionsDataHandling.h FunctionsTemplate.h FunctionsImplement.h
	g++ -c FunctionsIO.cpp

clean:
	-rm *.o bs

reset:
	-rm STATE_ROOM.txt STATE_LAB.txt STATE_LEC.txt