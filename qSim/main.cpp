//qSim by Daniel McDonough 9/29/17
#include <cstdlib>
#include "Event.h"
#include "Customer.h"
#include "Teller.h"
#include <iostream>
using namespace std;
//qSim #customer #teller #simtime #avgservicetime <seed>

//simulation time will be a linked list of seconds

void custFarm(int customers,int simtime){
	Customer* custObjPtr = new Customer[customers];
	//customerFarm is an array of customers
	for(int i = 0; i <= customers; i++){
		//Customer[i]
	}
}

void tellerFarm(int teller,int servtime){
	//Tellerfarm is an array of tellers
	Teller* tellObjPtr = new Teller[teller-1];
	for(int i = 0; i <= teller-1;i++){
		tellObjPtr[i].getidleTime();

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
}
