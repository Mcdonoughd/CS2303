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
	; //tellerline is populated with customer ID
	//write function to search through customers and check ID's in Customer.cpp
	int tellerLineLength;
public:
	tellerQueue();
	deque <int> tellerLine; //deque was used because std::priority queues do not allow iteration
	int getCustomerid(int pos);
	int getTellerLineLength();
	void setTellerLineLength();
	void addCustomer(int id);
	void removeCustomer();
	void removeCustomerCheck(Customer* Jim);
	virtual ~tellerQueue();
};



#endif
