
CFLAGS = -g -Wall

main: Customer.o Event.o eventQueue.o Stats.o Teller.o tellerQueue.o
	g++ $(CFLAGS) Customer.o Event.o eventQueue.o Stats.o Teller.o tellerQueue.o main.o docs -o qSim -lm

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -lm

Customer.o: Customer.cpp Customer.h
	g++ $(CFlAGS) -c Customer.cpp

Event.o: Event.cpp Event.h
	g++ $(CFLAGS) -c Event.cpp

eventQueue.o: eventQueue.cpp eventQueue.h
	g++ $(CFLAGS) -c eventQueue.cpp

Stats.o: Stats.cpp Stats.h
	g++ $(CFLAGS) -c Stats.cpp

Teller.o: Teller.cpp Teller.h
	g++ $(CFLAGS) -c Teller.cpp

tellerQueue.o: tellerQueue.cpp tellerQueue.h
	g++ $(CFLAGS) -c tellerQueue.cpp

docs: doxygen

all: main docs

clean:
	rm -f *.o qSim
