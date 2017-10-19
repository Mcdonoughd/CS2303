//Event.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Event.h"
#include <iostream>
int Event::id = 0;

Event::Event() {
	// TODO Auto-generated constructor stub
	duration = 0;
	time = 5;
	ID = id;
	id++;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}
void Event::action() {
	std::cout << "WRONG" << std::endl;
}
