
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

// The functions contained within this class are all getters and setters.
tellerQueue::tellerQueue(){
	tellerLineLength = this->getTellerLineLength();
	deque <int> tellerLine;
}//

int tellerQueue::getTellerLineLength(){
	this->setTellerLineLength();
	return this->tellerLineLength;
}

void tellerQueue::setTellerLineLength(){
	tellerLineLength = tellerLine.size();
}

void tellerQueue::addCustomer(int id){
	tellerLine.push_back(id);
}

void tellerQueue::removeCustomer(){
		tellerLine.pop_front();
		setTellerLineLength();
}
int tellerQueue::getCustomerid(int pos){
	return tellerLine[pos];
}
void tellerQueue::removeCustomerCheck(Customer* Jim){
	if(this->tellerLine.front()==Jim->getid()){
		this->tellerLine.pop_front();
		this->setTellerLineLength();
	}
}

 tellerQueue::~tellerQueue(){

}
