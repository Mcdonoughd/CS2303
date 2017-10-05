//Makefile for PA-4 for CS-2303 A'17 @ WPI by
//Surya Vadivazhagu and Daniel McDonough

CFLAGS = -g -Wall

main: main.o Customer.o Event.o eventQueue.o Stats.o Teller.o tellerQueue.o docs -o qSim -lm

main.o: main.cpp 
	g++ $(FLAGS) -c main.cpp -lm

Customer.o: Customer.cpp Customer.h
	g++ $(FlAGS) -c Customer.cpp
	
Event.o: Event.cpp Event.h
	g++ $(FLAGS) -c Event.cpp
	
eventQueue.o: eventQueue.cpp eventQueue.h
	g++ $(FLAGS) -c eventQueue.cpp
	
Stats.o: Stats.cpp Stats.h
	g++ $(FLAGS) -c Stats.cpp

Teller.o: Teller.cpp Teller.h
	g++ $(FLAGS) -c Teller.cpp

tellerQueue.o: tellerQueue.cpp tellerQueue.h
	g++ $(FLAGS) -c tellerQueue.cpp

all: main

docs: doxygen

clean:
	rm -f *.o qSim
