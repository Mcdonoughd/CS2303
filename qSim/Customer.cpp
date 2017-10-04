//Customer.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Customer.h"
#include "Teller.h"
#include <cmath>
Customer::Customer(){
	ID = 0;
	waitTime = 0;
	arrTime = rand()/float(RAND_MAX);
	actiontime = arrTime;
}
Customer::Customer(int id, int simTime){
	ID = id;
	waitTime = 0;
	arrTime = (simTime * rand()%100)/float(RAND_MAX);
	actiontime = arrTime;
}
void Customer::Action(){

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
	printf("%d %.2f--> NULL\n",this->actiontime,this->arrTime);
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
