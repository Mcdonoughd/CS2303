//Teller.cpp written by Daniel McDonough and Surya Vadivazhagu
#include "Teller.h"
#include "Bank.h"

float Teller::averageServiceTime = 0;

Teller::Teller() {
	// TODO Auto-generated constructor stub

	ID += 500;
	idleTime = 1;
	this->time = 10;
	serviceTime = 0;
}

Teller::~Teller() {
	// TODO Auto-generated destructor stub
}

void Teller::action(void) {
	Event* t = eventQueue.top();
	eventQueue.pop();
	serviceTime = 2 * averageServiceTime * rand() / float(RAND_MAX);
	if (!line.empty()) {
		totalServiceTime += serviceTime;
		//cout << "Teller Action | " << line.front()->ID << " | " << endl;
		Customer* c = line.front();
		maxWaitTime = max(maxWaitTime, simTime - c->arrivalTime);
		c->time = simTime + serviceTime;
		c->served = true;

		t->time = simTime + serviceTime; //Set teller event

		eventQueue.push(c);
		eventQueue.push(t);
		//cout << "New Customer Time " << c->ID << " " << c->time << " "
		//	<< t->time << endl;
		line.pop();
	} else {
		if (useCommonQueue && !commonQueue.empty()) {
			line.push(commonQueue.top());
			commonQueue.pop();
			action();

		}
		serviceTime = 150 * rand() / float(RAND_MAX) + 1;
		t->time = simTime + serviceTime;
		idleTime += serviceTime;
		//cout << serviceTime << endl;
		eventQueue.push(t);

	}

}

void Teller::addCustomer(void) {

}
