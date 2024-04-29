# Makefile Elevator

CXX = g++
CXXFLAGS_DEBUG = -Wall -g

release: ./src/main.o ./src/Elevator.o
	$(CXX) -o Elevator.out ./src/main.o ./src/Elevator.o

debug: ./src/main.o ./src/Elevator.o
	$(CXX) $(CXXFLAGS_DEBUG) -o Elevator.out ./src/main.o ./src/Elevator.o

main.o: ./src/main.cpp ./src/Elevator.h

Elevator.o:	./src/Elevator.h

clean:
	rm -f ./src/*.o;
	rm -f *.out
