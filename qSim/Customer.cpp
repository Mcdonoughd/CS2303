//Customer.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Customer.h"
#include "Bank.h"

Customer::Customer(int time) {
	this->time = time;
	this->arrivalTime = time;
	served = false;
}

Customer::~Customer() {
	// TODO Auto-generated destructor stub
}

void Customer::action(void) {
	eventQueue.pop();
	//cout << "Customer Action | " <<ends;
	if (!this->served) {
		//cout << "Adding to teller Line " << this->ID << endl;
		if (useCommonQueue) {
			commonQueue.push(this);
		} else {
			Teller* shortest = tellers.top();
			shortest->line.push(this);
			tellers.pop();
			tellers.push(shortest);
		}
	} else {
		//cout << "Removing from line " << this->ID << endl;
		totalCustomerTime += (simTime - arrivalTime);
		delete this;
	}
}
