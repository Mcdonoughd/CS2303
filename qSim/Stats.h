/*
 * Stats.h
 *  Created on: Oct 8, 2017
 *  Authors: Daniel McDonough and Surya Vadivazhagu
 */

#ifndef STATS_H_
#define STATS_H_
#include <iostream>
#include <string>
//#include "Teller.h"
//#include "Customer.h"
using namespace std;
class Stats {
private:


public:
	Stats();
	string QueueType = "";
	int totalWaitingTime = 0;
	int totalServiceTime = 0;
	int totalCustomers = 0;
	int totalTellers = 0;
	int avgWaitingTime = 0;
	int StDivWaitingTime = 0;
	int totalIdleTime = 0;
	int maxWaitTime = 0;
	void Print_Stats();
	~Stats();

};

#endif /* STATS_H_ */
