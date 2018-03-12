/*
 * Customer.h
 *
 *  Created on: Oct 8, 2017
 *      Authors: Daniel McDonough and Surya Vadivazhagu
 */
//
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "Event.h"
#include <cstdlib>

class Customer: public Event {
public:
	using Event::action;
	bool served;
	int arrivalTime;
	void action(void);
	Customer(int time);
	virtual ~Customer();
};

#endif /* CUSTOMER_H_ */
