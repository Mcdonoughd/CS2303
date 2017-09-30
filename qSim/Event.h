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
 void action();

public:
	Event();

	~Event();
};

#endif /* EVENT_H_ */
