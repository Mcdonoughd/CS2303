//Customer.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Customer.h"
#include "Teller.h"
#include <cmath>
#include "Stats.h"


Customer::Customer(){
	ID = 0;
	waitTime = 0;
	arrTime = rand()/float(RAND_MAX);
	actiontime = arrTime;
	hasbeenserved = false;
}
Customer::Customer(int id, int simTime){
	ID = id;
	waitTime = 0;
	arrTime = (simTime * rand()%100)/float(RAND_MAX);
	actiontime = arrTime;
	hasbeenserved = false;
}

/** Calculates the shortest line out of the Teller's lines
 * @param tellerobjptr Teller
 * @param tellers integer representing how many tellers exist
 * @return The integer representing the shortest line.
 */
int Customer::getshortestline(Teller* tellerobjptr,int tellers){
	unsigned int smallestline =10000;//if you have a line over 10000 customers long you either run a really good business or a really bad one
	int teller_with_smallest_line; //keeps track of the teller's position in the array with the smallest line.
	for(int i=0;i<=tellers-1;i++){
		if(tellerobjptr[i].getTellerQueue()->tellerLine.size()<smallestline){
			smallestline = tellerobjptr[i].getTellerQueue()->tellerLine.size();
			teller_with_smallest_line = i;
		}
		else if(tellerobjptr[i].getTellerQueue()->tellerLine.size()==smallestline){
			int a=rand()%2; //get rand number 1 or 0
			if(a==1){
				smallestline = tellerobjptr[i].getTellerQueue()->tellerLine.size();
				teller_with_smallest_line = i;
			}
			else{/*Keep the old line as the smallest line*/}
		}
	}
	return teller_with_smallest_line;
}

/** Creates an Action that Customers and Tellers can manipulate
 * @param tellerobjptr Pointer to a Teller
 * @param tellers integer representing the number of tellers
 * @param currTime current time in the simulation's clock
 * @param simTime the simulation time
 * @param seed the optionally inputted seed.
 * @param stats pointer to the statistics of the simulation
 * @return nothing (void function)
 */
void Customer::Action(Teller* tellerobjptr,int tellers,int currTime,int simTime,int seed,Stats* stats){
	printf("Customer %d has arrived!\n",this->ID);
	int shortline = getshortestline(tellerobjptr,tellers);
	tellerobjptr[shortline].getTellerQueue()->tellerLine.push_back(this->getid());
	printf("Customer %d has joined Line %d!\n",this->ID,tellerobjptr[shortline].getid());
	cout << "Line " << tellerobjptr[shortline].getid() <<" has "<<tellerobjptr[shortline].getTellerQueue()->tellerLine.size()<<" People!\n";

}

int Customer::getactiontime(){
	return this->actiontime;
}
bool Customer::checkid(int num){
	if(num == this->ID){
		return true;
	}
	return false;
}
int Customer::getid(){
	return this->ID;
}
void Customer::setid(int ID){
	this->ID = ID;
	////printf("%d",ID);
}
int Customer::getWaitTime(){
	return this->waitTime;
}
void Customer::setWaitTime(int waitTime){
	this->waitTime = waitTime;
}
int Customer:: getArrTime(){
	return this->arrTime;
}
void Customer::setArrTime(int simTime){
	this->arrTime = (simTime * rand())/float(RAND_MAX);
	actiontime = abs(this->arrTime * 100);
	//printf("%d %.2f--> NULL\n",this->actiontime,this->arrTime);
}
void  Customer::Print(){
	if(this->Next()!= NULL){
		printf("%d --> %d\n",this->actiontime, this->Next()->actiontime);
	}
	else{
		printf("%d %.2f--> NULL\n",this->actiontime,this->arrTime);
	}
}
Customer::~Customer(){

}
