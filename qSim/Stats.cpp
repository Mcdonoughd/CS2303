#include "Stats.h"
#include <iostream>
using namespace std;
Stats::Stats(){

}
Stats::~Stats(){

}
int Stats::Print_Stats(){
	cout<<"Queue Type:  "<<this->QueueType<<endl;
	cout<<"Total Waiting Time:   "<<this->totalWaitingTime<<endl;
	cout<<"Total Service Time:   "<<this->totalServiceTime<<endl;
	cout<<"Total Customers Served:   "<<this->totalCustomers<<endl;
	cout<<"Total Tellers Working:   "<<this->totalTellers<<endl;
	cout<<"Average Working Time:   "<<this->avgWaitingTime<<endl;
	cout<<"St. Div. Waiting Time:   "<<this->StDivWaitingTime<<endl;
	cout<<"Total Idle Time:   "<<this->totalIdleTime<<endl;
	cout<<"Max Waiting Time:   "<<this->maxWaitTime<<endl;
return 0;
}
