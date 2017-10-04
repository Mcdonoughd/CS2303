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
class tellerQueue{//
private:
	priority_queue <int> tellerLine; //tellerline is populated with customer ID
	//write function to search through customers and check ID's in Customer.cpp
	int tellerLineLength;
public:
	tellerQueue();
	int getTellerLineLength();
	void setTellerLineLength();
	void addCustomer(Customer Jim);
	void removeCustomer();
	void removeCustomerCheck(Customer Jim);
	virtual ~tellerQueue();
};



#endif
