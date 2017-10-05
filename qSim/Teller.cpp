//Teller.cpp written by Daniel McDonough and Surya Vadivazhagu
#include "Teller.h"
#include "Event.h"
#include <cstdlib>
#include "tellerQueue.h"
Teller::Teller(){
	this->totalServed = 0;
	this->servTime = 0;
	this->idleTime = 0;
	this->ID = 0;
	this->workingtime = 0;
	actiontime = workingtime;
	new tellerQueue;
	priority_queue <int> tellersLine;
}

Teller::Teller(int id, int avgServTime){
	this->ID = id;
	this->totalServed = 0;
	this->servTime = 2*avgServTime*rand()/float(RAND_MAX);
	this->idleTime = 0;
	this->workingtime = 0;
	actiontime = workingtime;
	new tellerQueue;
	priority_queue <int> tellersLine;
}
void Teller::Action(Teller* tellerobjptr,int tellers,int currTime,int simTime,int seed){
	printf("Teller %d Looks into their line...\n",this->getid());
	if(this->getTellerQueue().size()>0){
		printf("Teller %d is helping a customer...\n",this->getid());
		this->getTellerQueue().pop();
		this->setactiontime(this->getservTime() + this->setidleTime()+currTime);
		//check if goes over simTime for stats
		return;
	}
	else{
		for(int i=0; i<=tellers-1;i++){
			printf("Teller %d Looks into Teller's %d line...\n",this->getid(),tellerobjptr[i].getid());
			if(tellerobjptr[i].getTellerQueue().size()>0){
				printf("Teller %d is helping a customer from Teller's %d line...\n",this->getid(),tellerobjptr[i].getid());
				tellerobjptr[i].getTellerQueue().pop();
				this->setactiontime(this->getservTime() + this->setidleTime()+currTime);
				//check if goes over simTime for stats
			}
		}
		printf("Teller %d couldn't find any Customers, so they went on break...\n",this->getid());
		this->setactiontime(this->setidleTime()+currTime);
		//check if goes over simTime for stats
	}
}
priority_queue <int> Teller::getTellerQueue(){
	return tellersLine;
}
int Teller::gettotalServed(){
	return this->totalServed;
}
void Teller::settotalServed(int serv){
	this->totalServed = serv;
}
int Teller::getactiontime(){
	return this->actiontime;
}
float Teller::getservTime(){
	//printf("%.2f\n",this->servTime);
	return this->servTime;
}
void Teller::setservTime(int stime){
	this->servTime = 2*stime*rand()/float(RAND_MAX);;
}
int Teller::getidleTime(){
	printf("%d\n",idleTime);
	return idleTime;
}
int Teller::setidleTime(){
	this->idleTime = rand()%150;
	return this->idleTime;
}
int Teller::getid(){
	return this->ID;
}
void Teller::setid(int id){
	this->ID = id;
}
Teller::~Teller(){
	//this->tellerLine.~tellerQueue();
}
