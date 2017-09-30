/*
 * tellerQueue.h
 *	 Created on: 9/29/2017
 *      Authors: Daniel Mcdonough and Surya Vadivazhagu
 */
#ifndef TELLERQUEUE_H_
#define TELLERQUEUE_H_

#include <iostream>
#include <string>
#include <queue>
#include "Customer.h"
using namespace std;
class tellerQueue{
private:
	priority_queue <Customer> tellerLine;
	int tellerLineLength;
public:
	tellerQueue();
	int getTellerLineLength();
	void setTellerLineLength();
	void addCustomer(Customer Jim);
	void removeCustomer(Customer Jim);
	~tellerQueue();
};



#endif
