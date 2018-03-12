#include <queue>
#include <typeinfo>
#include "Bank.h"
#include "Customer.h"

TellerQueue tellers;
EventQueue eventQueue;
CommonQueue commonQueue;

int simTime = 0;

float totalServiceTime = 0;
float totalCustomerTime = 0;
int maxWaitTime = 0;
int idleTime = 0;
bool useCommonQueue = false;

int main(int argc, char * argv[]) {
	srand(time(NULL));
	int customers = atoi(argv[1]); //atoi(argv[1]);
	int numTellers = atoi(argv[2]);
	float simulationTime = atof(argv[3]);

	float averageServiceTimes = atof(argv[4]);
	Teller::averageServiceTime = averageServiceTimes;

	if (argc == 6)
		srand(atoi(argv[5]));

	for (int i = 0; i < numTellers; i++) {
		Teller* t = new Teller();
		tellers.push(t);
		eventQueue.push(t);
	}

	for (int i = 0; i < customers; i++) {
		Event * cust = new Customer((simulationTime * rand() / RAND_MAX) + 1);
		eventQueue.push(cust);
	}

	Event* tmp;
	//printQueue(eventQueue);
	while (simTime < simulationTime) {
		//eventQueue.top()->action();
		//cout << simTime << " =================== " << endl;
		tmp = eventQueue.top();
		while (simTime == tmp->time) {
			tmp->action();
			if (!eventQueue.empty()) {
				tmp = eventQueue.top();

			}

		}
		//printQueue(eventQueue);
		//cout << endl;
		simTime++;
	}
	cout << "Number of Customers Served: " << customers << endl;
	cout << numTellers << " Tellers - Queue per Teller" << endl;
	cout << "Max wait time: " << maxWaitTime << endl;
	cout << "Average Time Spent in Bank: " << totalCustomerTime / customers
			<< endl;
	cout << "Total Service Time " << totalServiceTime << endl;
	cout << "Total Teller Idle Time: " << idleTime << endl;

	maxWaitTime = 0;
	totalCustomerTime = 0;
	totalServiceTime = 0;
	idleTime = 0;

	useCommonQueue = true;
	while (!eventQueue.empty()) {
		eventQueue.pop();
	}

	for (int i = 0; i < customers; i++) {
		Event * cust = new Customer((simulationTime * rand() / RAND_MAX) + 1);
		eventQueue.push(cust);
	}

	for (int i = 0; i < numTellers; i++) {
		eventQueue.push(new Teller());
	}
	simTime = 0;

	while (simTime < simulationTime) {
		//eventQueue.top()->action();
		//cout << simTime << " =================== " << endl;
		tmp = eventQueue.top();
		while (simTime == tmp->time) {
			tmp->action();
			if (!eventQueue.empty()) {
				tmp = eventQueue.top();

			}

		}
		//printQueue(eventQueue);
		//cout << endl;
		simTime++;
	}
	cout << "\n\n\n";
	cout << "Number of Customers Served: " << customers << endl;
	cout << numTellers << " Tellers - Common Queue" << endl;
	cout << "Max wait time: " << maxWaitTime << endl;
	cout << "Average Time Spent in Bank: " << totalCustomerTime / customers
			<< endl;
	cout << "Total Service Time " << totalServiceTime << endl;
	cout << "Total Teller Idle Time: " << idleTime << endl;
}

void printQueue(EventQueue q) {
	EventQueue tmp(q);
	cout << "Q: " << tmp.size() << endl;
	int end = tmp.size();
	for (int i = 0; i < end; i++) {
		cout << "Customer " << i + 1 << ": " << tmp.top()->ID << " - "
				<< tmp.top()->time << endl;
		tmp.pop();
	}
}
