/*
 * Event.h
 *  Created on: Oct 8, 2017
 *  Authors: Daniel McDonough and Surya Vadivazhagu
 */
//
#ifndef EVENT_H_
#define EVENT_H_
#include <iostream>
#include <string>
class Teller;
//#include "Teller.h"
//#include "Customer.h"
class Stats;
using namespace std;
class Event {
private:

protected:


public:
	Event();
	int actiontime;
	Event *next;
	void Print();
	virtual void Action(Teller* tellerobjptr,int tellers,int currTime,int simTime,int seed,Stats* stat) = 0 ;
	virtual int getactiontime();
	virtual void setactiontime(int update);
	void SetNext(Event* aNext);
	Event* Next();
	virtual ~Event();

};

#endif /* EVENT_H_ */
