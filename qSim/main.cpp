//qSim by Daniel McDonough and Surya Vadivazhagu 9/29/17
#include <cstdlib>
#include "Event.h"
#include "Customer.h"
#include "Teller.h"
#include "tellerQueue.h"
#include "eventQueue.h"
#include <iostream>
#include <list>
using namespace std;
//qSim #customer #teller #simtime #avgservicetime <seed>

//simulation time will be a linked list of seconds

void custFarm(int customers,int simtime){

	Customer* custObjPtr = new Customer[customers];
	//customerFarm is an array of customers
	for(int i = 0; i <= customers; i++){
		//initialize id for all customer
		custObjPtr[i].setid(i+1);
		//initalize random arrival times
		custObjPtr[i].setArrTime(simtime);
	}
}
void tellerFarm(int teller,int servtime){
	//Tellerfarm is an array of tellers
	Teller* tellObjPtr = new Teller[teller];
	for(int i = 0; i <= teller-1;i++){
		//tellObjPtr[i].getservTime();
		//initalize id for all tellers
		tellObjPtr[i].setid(i+1);
		//inialize random service time
		tellObjPtr[i].setservTime(servtime);
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
	//int rand = 0;
	if(argc>5){
		if(atoi(argv[5]) != 0){
				srand(atoi(argv[5]));
			}
	}

	tellerFarm(teller,servtime);
	custFarm(customers,simtime);
}
