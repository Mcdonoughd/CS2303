#include "Teller.h"
Teller::Teller(){
	this->totalServed = 0;
	this->servTime = 0;
	this->idleTime = 0;
	this->ID = 0;
}

Teller::Teller(int id, int avgServTime){
	this->ID = id;
	this->totalServed = 0;
	this->servTime = 2*avgServTime*rand()/float(RAND_MAX);
	this->idleTime = 0;
}
int Teller::gettotalServed(){
	return this->totalServed;
}
void Teller::settotalServed(int serv){
	this->totalServed = serv;
}
float Teller::getservTime(){
	printf("%.2f\n",this->servTime);
	return this->servTime;
}
void Teller::setservTime(int stime){
	this->servTime = stime;
}
int Teller::getidleTime(){
	printf("%d\n",idleTime);
	return idleTime;
}
void Teller::setidleTime(int idle){
	this->idleTime = idle;
}
int Teller::getid(){
	return this->ID;
}
void Teller::setid(int id){
	this->ID = id;
}
Teller::~Teller(){

}
