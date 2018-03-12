/*
 * Teller.h
 *
 *  Created on: 9/29/2017
 *      Authors: Daniel Mcdonough and Surya Vadivazhagu
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <queue>
#include "Event.h"
#include "Customer.h"
using namespace std;

class Teller: public Event {
public:
	static float averageServiceTime;
	int time;
	int serviceTime;
	queue<Customer *> line;
	void action();
	void addCustomer();
	Teller();
	virtual ~Teller();

};

#endif /* TELLER_H_ */
