#include "Customer.h"
Customer::Customer(int id, int simTime){
	ID = id;
	waitTime = 0;
	arrTime = simTime * rand()/float(RAND_MAX);
}
