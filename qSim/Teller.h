/*
 * Teller.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Daniel Mcdonough
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
