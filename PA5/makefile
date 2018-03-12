#
#  makefile
#
#  Created on: Feb 17, 2017
#      Author: Nugzar Chkhaidze & Daniel Sullivan
#
CFLAGS =  -g -Wall

all: PA5

PA5: Rational.o
	g++ $(CFLAGS) Rational.o -o PA5

Rational.o: Rational.cpp Rational.h
	g++ $(CFLAGS) -c Rational.cpp

clean:
	rm -f *.o *.exe PA5