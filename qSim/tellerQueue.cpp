
/*
 * tellerQueue.cpp
 *	 Created on: 9/29/2017
 *      Authors: Daniel McDonough and Surya Vadivazhagu
 */
#include "tellerQueue.h"
#include <iostream>
#include <string>
using namespace std;

tellerQueue::tellerQueue(){
	tellerLineLength = this->getTellerLineLength();
}

int tellerQueue::getTellerLineLength(){
	this->setTellerLineLength();
	return this->tellerLineLength;
}

void tellerQueue::setTellerLineLength(){
	this->tellerLineLength = this->tellerLine.size();
}

void tellerQueue::addCustomer(Customer Jim){
	this->tellerLine.push(Jim.getid());
}

void tellerQueue::removeCustomer(){
		this->tellerLine.pop();
}

void tellerQueue::removeCustomerCheck(Customer Jim){
	if(this->tellerLine.top()==Jim.getid()){
		this->tellerLine.pop();
	}
}

 tellerQueue::~tellerQueue(){

}
