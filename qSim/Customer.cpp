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
Customer::~Customer(){

}
