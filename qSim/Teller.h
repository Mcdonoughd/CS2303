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
using namespace std;

class Teller : public Event {
private:
	int ID;
	int totalServed;
	float servTime;
	int idleTime;
public:
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
