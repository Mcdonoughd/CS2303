#include "Stats.h"
using namespace std;
Stats::Stats(){

}
Stats::~Stats(){

}
void Stats::Print_Stats(){
	cout<<"Queue Type:  "<<QueueType<<endl;
	cout<<"Total Waiting Time:   "<<totalWaitingTime<<endl;
	cout<<"Total Service Time:   "<<totalServiceTime<<endl;
	cout<<"Total Customers Served:   "<<totalCustomers<<endl;
	cout<<"Total Tellers Working:   "<<totalTellers<<endl;
	cout<<"Average Working Time:   "<<avgWaitingTime<<endl;
	cout<<"St. Div. Waiting Time:   "<<StDivWaitingTime<<endl;
	cout<<"Total Idle Time:   "<<totalIdleTime<<endl;
	cout<<"Max Waiting Time:   "<<maxWaitTime<<endl;

}
