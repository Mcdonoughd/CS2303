//Teller.cpp written by Daniel McDonough and Surya Vadivazhagu
#include "Teller.h"
#include "Event.h"
#include <cstdlib>
#include "Stats.h"
#include "tellerQueue.h"
Teller::Teller(){
	tellerLine = new tellerQueue;
	this->totalServed = 0;
	this->servTime = 0;
	this->idleTime = 0;
	this->ID = 0;
	this->workingtime = 0;
	actiontime = workingtime;
}

void Teller::settellerQ(tellerQueue* t){
	this->tellerLine = t;
}
/** oversimtime returns a bool depending upon whether they are over the sim time or not.
 * @param curr int representing the current time
 * @param sim int representing the simtime
 * @return boolean whether they are over the sim time or not.
 *
 */
bool Teller::oversimtime(int curr,int sim){
	if((this->getservTime() + this->getidleTime()+curr )>sim){
		return true;
	}
	return false;
}
bool Teller::oversimtimeidle(int curr,int sim){
	if((this->getidleTime()+curr )>sim){
		return true;
	}
	return false;
}
/** LoadStatsIdle loads the current statistics when the sim is idle.
 * @param int currTime is the current time in the simulation.
 * @param simTime is the simulations' overall time
 * @param stat is the instance of the statistics class that records stats for the simulation.
 * @return void as nothing is being returned.
 *
 */
void Teller::LoadStatsIdle(int currTime,int simTime,Stats* stat){
	int LegitIdleTime;
	if(this->oversimtimeidle(currTime,simTime)){
		if (this->getidleTime()-(simTime-currTime) < 0){
							LegitIdleTime = this->getidleTime()-(this->getidleTime()-(simTime-currTime));
						}
						else{
							//then Count ServTime in stats
							LegitIdleTime = this->getidleTime();
						}
		stat->totalIdleTime+=LegitIdleTime;
	}
}
/** LoadStats loads the stats for a particular time
 * @param currTime the current time
 * @param simTime the simulation's time
 * @param stat the instance of statistics class that holds the stats for the event.
 * @return void, as it updates.
 */
void Teller::LoadStats(int currTime,int simTime,Stats* stat){
	int LegitServTime;
	int LegitIdleTime;
	if(this->oversimtime(currTime,simTime)){
				//add to stats:

				if (this->getservTime()-(simTime-currTime) < 0){
					LegitServTime = this->getservTime()-(this->getservTime()-(simTime-currTime));
				}
				else if (this->getservTime()-(simTime-currTime) == 0){
					//then Count ServTime in stats
					LegitServTime = this->getservTime();
				}
				else{
					if(this->getservTime()-(simTime-currTime) > 0){
						if(this->getidleTime()-(this->getservTime()-(simTime-currTime)) < 0){
							LegitIdleTime = (this->getidleTime() - (this->getidleTime()-(this->getservTime()-(simTime-currTime))));
							LegitServTime = this->getservTime();
						}
					}
					else {
						LegitIdleTime =this->getidleTime();
						LegitServTime = this->getservTime();
					}

				}
				//if ServTime-(SIMTIME-CURRTIME) > 0 then:
				//if IdleTime-(ServTime-(SIMTIME-CURRTIME)) < 0 then
				//LegitIdletime = IdleTime - (IdleTime-(ServTime-(SIMTIME-CURRTIME)); LegitServeTime = ServeTime
				//if IdleTime-(ServTime-(SIMTIME-CURRTIME)) == 0 then Both are legit.(should never get to this case)

			}
	//add serve time and idle time to stats
				stat->totalServiceTime+=LegitServTime;
				stat->totalIdleTime+=LegitIdleTime;
}
/** Action is a teller's action
 * @param tellerobjptr is a pointer to a teller
 * @param tellers is an int representing the # of tellers.
 * @param currTime is the current time.
 * @param simTime is the simulation's time.
 * @param seed is the optionally inputted seed.
 * @param stat is the statistics that keeps track of the stats for the given simulation.
 *
 */

void Teller::Action(Teller* tellerobjptr,int tellers,int currTime,int simTime,int seed,Stats* stat){
	printf("Teller %d Looks into their line...\n",this->getid());

	if(!(this->getTellerQueue()->tellerLine.empty())){
		printf("Teller %d is helping a customer...\n",this->getid());
		this->getTellerQueue()->removeCustomer();
		stat->totalCustomers++;
		this->setactiontime(this->getservTime() + this->setidleTime()+currTime);


		this->LoadStats( currTime,simTime,stat);
		//check if goes over simTime for stats
		return;
	}
	else{
		for(int i=0; i<=tellers-1;i++){
			printf("Teller %d Looks into Teller's %d line...\n",this->getid(),tellerobjptr[i].getid());
			if(!(tellerobjptr[i].getTellerQueue()->tellerLine.empty())){
				printf("Teller %d is helping a customer from Teller's %d line...\n",this->getid(),tellerobjptr[i].getid());
				tellerobjptr[i].getTellerQueue()->removeCustomer();
				stat->totalCustomers++;
				this->setactiontime(this->getservTime() + this->setidleTime()+currTime);
				this->LoadStats( currTime,simTime,stat);
				return;
			}
		}
		printf("Teller %d couldn't find any Customers, so they went on break...\n",this->getid());
		this->setactiontime(this->setidleTime()+currTime);
		//check if goes over simTime for stats (not similar to for loop above because this only counts idleTime
		//add to stats:
		//if IdleTime-(SIMTIME-CURRTIME) is < 0 then:
		//LegitIdleTime = IdleTime-(IdleTime-(SIMTIME-CURRTIME))
		//if IdleTime-(SIMTIME-CURRTIME) == 0 then Count IdleTime in stats
		LoadStatsIdle(currTime, simTime, stat);
	}
}
//The following functions are all getters or setters for Tellers.
tellerQueue* Teller::getTellerQueue(){
	return tellerLine;
}
int Teller::gettotalServed(){
	return this->totalServed;
}
void Teller::settotalServed(int serv){
	this->totalServed = serv;
}
int Teller::getactiontime(){
	return this->actiontime;
}
float Teller::getservTime(){
	//printf("%.2f\n",this->servTime);
	return this->servTime;
}
void Teller::setservTime(int stime){
	this->servTime = 2*stime*rand()/float(RAND_MAX);;
}
int Teller::getidleTime(){
	//printf("%d\n",idleTime);
	return idleTime;
}
int Teller::setidleTime(){
	this->idleTime = rand()%150;
	return this->idleTime;
}
int Teller::getid(){
	return this->ID;
}
void Teller::setid(int id){
	this->ID = id;
}
Teller::~Teller(){
	//this->tellerLine.~tellerQueue();
}
