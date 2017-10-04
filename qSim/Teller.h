/*
 * Teller.h
 *
 *  Created on: 9/29/2017
 *      Authors: Daniel Mcdonough and Surya Vadivazhagu
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <iostream>
#include <string>
#include "Event.h"
#include "tellerQueue.h"
using namespace std;

class Teller : public Event {
private:

	int ID; //A teller's ID
	int totalServed; //Count of how many customers a teller has served
	float servTime; //the amount of time it takes for a teller to serve a customer
	int idleTime; // the amount of time a teller goes inactive after serving a customer
	int workingtime; // the current time at which a teller is working
	tellerQueue tellerLine; //the line in front of a teller
public:
	void Action() override;
	int getactiontime();
	tellerQueue getTellerQueue();
	int gettotalServed();
	float getservTime();
	int getidleTime();
	void setidleTime(int idle);
	void setservTime(int stime);
	void settotalServed(int serv);
	int getid();
	void setid(int id);
	Teller();
	Teller(int id, int avgServTime);
	~Teller();
};

#endif /* TELLER_H_ */
