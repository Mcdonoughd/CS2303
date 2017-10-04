/*
 * Customer.h
 *
 *  Created on: Oct 8, 2017
 *      Authors: Daniel McDonough and Surya Vadivazhagu
 */
//
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <iostream>
#include <string>
#include "Event.h"
using namespace std;

class Customer:public Event{

private:
	//void action();
	int ID;
	float arrTime;
	int waitTime;

public:
	Customer();
	Customer(int ID, int simTime);
	~Customer();
	void Action() override;
	int getid();
	void Print();
	int getactiontime();
	void setid(int ID);
	int getWaitTime();
	void setWaitTime(int waitTime);
	int getArrTime();
	void setArrTime(int arrTime);
	bool checkid(int num);
};

#endif /* EVENT_H_ */
