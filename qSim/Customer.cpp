//Customer.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Customer.h"
Customer::Customer(){
	ID = 0;
	waitTime = 0;
	arrTime = rand()/float(RAND_MAX);
}
Customer::Customer(int id, int simTime){
	ID = id;
	waitTime = 0;
	arrTime = simTime * rand()/float(RAND_MAX);
}
int Customer::getid(){
	return this->ID;
}
void Customer::setid(int ID){
	this->ID = ID;
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
	this->arrTime = simTime * rand()/float(RAND_MAX);
}
Customer::~Customer(){

}
