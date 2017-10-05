/*
 * Stats.h
 *  Created on: Oct 8, 2017
 *  Authors: Daniel McDonough and Surya Vadivazhagu
 */
//
#ifndef STATS_H_
#define STATS_H_
#include <iostream>
#include <string>
//#include "Teller.h"
//#include "Customer.h"
using namespace std;
class Stats {
private://


public:
	Stats();
	string QueueType = "";
	int totalWaitingTime = 0;//done
	int totalServiceTime = 0;//done
	int totalCustomers = 0; //total customers served
	int totalTellers = 0; //given
	int avgWaitingTime = 0;
	int StDivWaitingTime = 0;
	int totalIdleTime = 0;//done
	int timeReq =0;
	int maxWaitTime = 0;//done
	int Print_Stats();//prints all stats except time Required!
	~Stats();

};

#endif /* STATS_H_ */
