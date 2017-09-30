
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
	//tellerLine;
	tellerLineLength = 0;
}
int tellerQueue::getTellerLineLength(){
	this->setTellerLineLength();
	return this->tellerLineLength;
}
void tellerQueue::addCustomer(Customer Jim){

}
void tellerQueue::removeCustomer(Customer Jim){

}
tellerQueue::~tellerQueue(){

}
