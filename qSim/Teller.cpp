#include "Teller.h"
Teller::Teller(){
	this->totalServed = 0;
	this->servTime = rand();
	this->idleTime = 0;
}


Teller::Teller(int avgServTime){
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
float getservTime(){

}
void setservTime(){

}
int getidleTime(){

}
void setidleTime(){

}
