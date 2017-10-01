
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

}
void tellerQueue::removeCustomer(Customer Jim){

}
 tellerQueue::~tellerQueue(){

}
