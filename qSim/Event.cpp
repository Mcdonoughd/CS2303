//Event.cpp by Daniel McDonough and Surya Vadivazhagu
#include "Event.h"

Event::Event(){
actiontime =0;
next = NULL;
}

Event::~Event(){

}


int Event::getactiontime(){
	return this->actiontime;
}

Event* Event::Next(){
	return this->next;
}
void  Event::Print(){
	if(this->Next()!= NULL){
	printf("%d --> %d\n",this->actiontime, this->Next()->actiontime);
	}
	else{
		printf("%d --> NULL\n",this->actiontime);
	}
}
void Event::SetNext(Event* aNext){
	this->next = aNext;
}

void Event::setactiontime(int update){
	this->actiontime += update;
}
