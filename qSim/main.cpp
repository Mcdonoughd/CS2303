//qSim by Daniel McDonough and Surya Vadivazhagu 9/29/17
#include <cstdlib>
#include "Event.h"
#include "Customer.h"
#include "Teller.h"
#include "tellerQueue.h"
#include "eventQueue.h"
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

//qSim #customer #teller #simtime #avgservicetime <seed>

//simulation time will be a linked list of seconds

void goThroughActions(int simtime,eventQueue* Clock){

	for(int i =0; i<=simtime; i++){
		//START SIMULATION!
		if(Clock->Exists(i)){
			//there is an event at this time!
		}




	}
	if(Clock->getsize()!=0){
	//if eventqueue is still not empty then continue until done but dont count stats
	}
}

void custFarm(Customer* custObjPtr, int customers, int simtime,eventQueue* Clock){
	//customerFarm is an array of customers
	for(int i = 0; i <= customers-1; i++){
		//initialize id for all customer
		custObjPtr[i].setid(i+1);
		//initalize random arrival times
		custObjPtr[i].setArrTime(simtime);
		Clock->Append(custObjPtr[i]);
		//custObjPtr[i].Print();
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
		Clock->Append(tellObjPtr[i]);
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
	srand((unsigned int) seconds);
	if(argc>5){
		if(atoi(argv[5]) != 0){
			srand(atoi(argv[5]));
		}
	}
	eventQueue *Clock;
	Clock = new eventQueue;
	Customer* custObjPtr = new Customer[customers];
	Teller* tellObjPtr = new Teller[teller];
	tellerFarm(tellObjPtr,teller,servtime,Clock);
	custFarm(custObjPtr,customers,simtime,Clock);
	return 0;
}
