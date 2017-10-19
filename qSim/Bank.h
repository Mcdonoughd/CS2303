#ifndef BANK_H_
#define BANK_H_
#include "Event.h"
#include "Teller.h"
#include <iostream>
using namespace std;

class CustomerComparator {
public:
	bool operator()(Event *c1, Event *c2) {
		return c1->time > c2->time;
	}
};

class TellerComparator {
public:
	bool operator()(Teller* t1, Teller* t2) {
		return t1->line.size() > t2->line.size();
	}
};

typedef std::priority_queue<Event*, std::vector<Event*>, CustomerComparator> EventQueue;

typedef std::priority_queue<Customer*, std::vector<Customer*>, CustomerComparator> CommonQueue;

typedef std::priority_queue<Teller*, std::vector<Teller*>, TellerComparator> TellerQueue;
void printQueue(EventQueue);

extern TellerQueue tellers;
extern EventQueue eventQueue;
extern CommonQueue commonQueue;

extern int maxWaitTime;
extern float totalServiceTime;
extern float totalCustomerTime;
extern int simTime;
extern int idleTime;
extern bool useCommonQueue;
#endif /* BANK_H_ */
