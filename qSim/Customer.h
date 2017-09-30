/*
 * Customer.h
 *
 *  Created on: Oct 8, 2017
 *      Authors: Daniel McDonough and Surya Vadivazhagu
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <string>
#include "Event.h"
using namespace std;

class Customer:public Event{

private:
	void action();
	int ID = 0;
	float arrTime = 0;
	int waitTime =0;

public:
	Customer();
	Customer(int ID, int simTime);
	~Customer();
	int getid();
	void setid(int ID);
	int getWaitTime();
	void setWaitTime(int waitTime);
	int getArrTime();
	void setArrTime(int arrTime);
};

#endif /* EVENT_H_ */
