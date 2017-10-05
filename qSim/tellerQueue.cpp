
/*
 * tellerQueue.cpp
 *	 Created on: 9/29/2017
 *      Authors: Daniel McDonough and Surya Vadivazhagu
 */
#include "tellerQueue.h"
#include <iostream>
#include <string>
#include <queue>
using namespace std;

tellerQueue::tellerQueue(){
	tellerLineLength = this->getTellerLineLength();
	priority_queue <int> tellerLine;
}//
priority_queue <int> tellerQueue::PriorityQ(){
	return this->tellerLine;
}
int tellerQueue::getTellerLineLength(){
	this->setTellerLineLength();
	return this->tellerLineLength;
}

void tellerQueue::setTellerLineLength(){
	tellerLineLength = tellerLine.size();
}

void tellerQueue::addCustomer(int id){
	tellerLine.push(id);
}

void tellerQueue::removeCustomer(){
		tellerLine.pop();
		setTellerLineLength();
}

void tellerQueue::removeCustomerCheck(Customer* Jim){
	if(this->tellerLine.top()==Jim->getid()){
		this->tellerLine.pop();
		this->setTellerLineLength();
	}
}

 tellerQueue::~tellerQueue(){

}
