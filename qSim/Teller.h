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

public:
	void Action(Teller* tellerobjptr,int tellers,int currTime,int simTime,int seed,Stats* stat) override;
	int getactiontime();
	void LoadStatsIdle(int currTime,int simTime,Stats* stat);
	void LoadStats(int currTime,int simTime,Stats* stat);
	bool oversimtime(int curr,int sim);
	bool oversimtimeidle(int curr,int sim);
	tellerQueue* tellerLine;//the line in front of a teller (made public for ease and due to time constraints
	void settellerQ(tellerQueue* t);
	tellerQueue* getTellerQueue();
	int gettotalServed();
	float getservTime();
	int getidleTime();
	int setidleTime();
	void setservTime(int stime);
	void settotalServed(int serv);
	int getid();
	void setid(int id);
	Teller();
	Teller(int id, int avgServTime);
	~Teller();
};
//
#endif /* TELLER_H_ */
