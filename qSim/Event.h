/*
 * Event.h
 *  Created on: Oct 8, 2017
 *  Authors: Daniel McDonough and Surya Vadivazhagu
 */

#ifndef EVENT_H_
#define EVENT_H_
#include <iostream>
#include <string>
//#include "Teller.h"
//#include "Customer.h"
using namespace std;
class Event {
private:

protected:
 int actiontime;
 Event *next;

public:
	Event();
	void Print();
	int getactiontime();
	void setactiontime(int update);
	void SetNext(Event* aNext);
	Event* Next();
	~Event();

};

#endif /* EVENT_H_ */
