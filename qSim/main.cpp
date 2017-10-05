//qSim by Daniel McDonough and Surya Vadivazhagu 9/29/17
#include <cstdlib>
#include "Event.h"
#include "Customer.h"
#include "Teller.h"
#include "tellerQueue.h"
#include "eventQueue.h"
#include <iostream>
#include <math.h>
#include <list>
#include <time.h>
#include "Stats.h"
#include <typeinfo>
using namespace std;
//qSim #customer #teller #simtime #avgservicetime <seed>

void TellersShareQ(Teller* tellObjptr2,int tellers){
	tellerQueue* p = tellObjptr2[0].tellerLine;
	for(int i=1;i<=tellers-1;i++){
		tellObjptr2[i].tellerLine = p;
	}
}
void updateTotalWaits(Customer* custObjPtr,int customers,Stats* stats){
	double waittimesqr=0;
	for(int i=0;i<=customers-1;i++){
		waittimesqr=(custObjPtr[i].getWaitTime()*custObjPtr[i].getWaitTime());
		stats->totalWaitingTime+=custObjPtr[i].getWaitTime();
	}

	stats->avgWaitingTime= stats->totalWaitingTime/customers;
	stats->StDivWaitingTime=(waittimesqr-(stats->avgWaitingTime*stats->avgWaitingTime));
}
void updateWait(int id,Customer* custObjPtr,int customers,Stats* stats){
	int maxWait=0;
	for(int i=0;i<=customers-1;i++){
		if(custObjPtr[i].checkid(id)){
			custObjPtr[i].setWaitTime(custObjPtr[i].getWaitTime()+1);
			if(custObjPtr[i].getWaitTime()>maxWait){
				//get customer stats here!
				maxWait=custObjPtr[i].getWaitTime();
			}
		}
	}
	stats->maxWaitTime=maxWait;
}
//simulation time will be a linked list of seconds
void goThroughActions(int simtime,eventQueue* Clock, Customer* custObjPtr, int customer,Teller* tellObjPtr,int tellers,int seed,Stats* stats){
	int customers_served = 0;
	int lowest_id = 10000000;
	int currTime = 0;
	while(currTime<=simtime){//have o keep track of customers
		printf("Time == %d\n",currTime);
		printf("%d Events at this time.\n",Clock->Exists(currTime));
		//START SIMULATION!
		int numEvents = Clock->Exists(currTime);
		if(numEvents>0){
			int eventcount = 0;
			for(;eventcount<numEvents;eventcount++){
				//there is an event at this time!
				Clock->getEvent(currTime)->Action(tellObjPtr,tellers,currTime,simtime,seed,stats);//do for all actions with similar action time

				//Clock->Action(i);
				//Clock->Delete(currTime);
			}
		}
		currTime++;//time updates
		//update time for all customers waiting in line (FOR THE STATS!)

		for(int j =0; j <= tellers-1; j++){
			int Maxlinesize = tellObjPtr[j].getTellerQueue()->tellerLine.size();
			stats->maxWaitTime=Maxlinesize;
			for(int linesize = 0;linesize<=Maxlinesize;linesize++){
				updateWait(tellObjPtr[j].getTellerQueue()->getCustomerid(linesize), custObjPtr,customer,stats);
				if(lowest_id>tellObjPtr[j].getTellerQueue()->getCustomerid(linesize)){
					lowest_id=tellObjPtr[j].getTellerQueue()->getCustomerid(linesize);
				}
			}
		}
		customers_served = lowest_id-1;
		if(customers_served == customer){
			break;
		}
	}
	updateTotalWaits(custObjPtr, customer, stats);
	//print all stats
	if(customers_served == customer){//if eventqueue is still not empty then continue until done but dont count stats (you can still count stats just dont print them ;)

	}
	//print last stat of total time required to serve all cust
}

void custFarm(Customer* custObjPtr, int customers, int simtime,eventQueue* Clock){
	//customerFarm is an array of customers
	for(int i = 0; i <= customers-1; i++){
		//initialize id for all customer
		custObjPtr[i].setid(i+1);
		//initalize random arrival times
		custObjPtr[i].setArrTime(simtime);
		//custObjPtr[i].Print();
		Clock->Append(&custObjPtr[i]); //adds entire customer pool to the clock one customer at a time
	}
}

void tellerFarm(Teller* tellObjPtr,int teller,int servtime,eventQueue* Clock){
	//Tellerfarm is an array of tellers
	for(int i = 0; i <= teller-1;i++){
		//tellObjPtr[i].getservTime();
		//initalize id for all tellers
		tellObjPtr[i].setid(i+1);
		//inialize random service time
		tellObjPtr[i].setservTime(servtime);
		Clock->Append(&tellObjPtr[i]);//add the entire teller pool to the clock one teller at a  time
	}
}

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "Please Initialize Proper Arguments!"<< endl;
		return 1;
	}
	int simtime = atoi(argv[3]); //simulation time
	int servtime = atoi(argv[4]); //avg serve time
	int customers = atoi(argv[1]); //number of customers
	int teller = atoi(argv[2]); //number of tellers

	//Declare variable to hold seconds on clock.
	time_t seconds;
	/*
	Get value from system clock and
	place in seconds variable.
	 */
	time(&seconds);
	/*
	Convert seconds to a unsigned
	integer.
	 */
	int seed = time(&seconds);
	srand((unsigned int) seconds);
	if(argc>5){
		if(atoi(argv[5]) != 0){
			srand(atoi(argv[5]));
			seed = atoi(argv[5]);
		}
	}
	//1st GO seperate tellerQ's
	eventQueue *Clock;
	Stats *stats;
	stats = new Stats;
	Clock = new eventQueue;
	Customer* custObjPtr = new Customer[customers];
	Teller* tellObjPtr = new Teller[teller];
	custFarm(custObjPtr,customers,simtime,Clock);
	tellerFarm(tellObjPtr,teller,servtime,Clock);
	goThroughActions(simtime,Clock,custObjPtr,customers,tellObjPtr,teller,seed,stats);
	//print
	eventQueue *Clock2;
	Stats *stats2;
	stats2 = new Stats;
	Clock2 = new eventQueue;
	Customer* custObjPtr2 = new Customer[customers];
	Teller* tellObjPtr2 = new Teller[teller];
	TellersShareQ( tellObjPtr2, teller);
	custFarm(custObjPtr2,customers,simtime,Clock2);
	tellerFarm(tellObjPtr2,teller,servtime,Clock2);
	goThroughActions(simtime,Clock2,custObjPtr2,customers,tellObjPtr2,teller,seed,stats2);
	return 0;
}
