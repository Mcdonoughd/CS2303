
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;


//Delare known constants from instructions
//constant for the world dimensions of 20x20
//const int MWS = 20; //max world size

//starting values for ants and doodlebugs

//values for returning Ants and Doodlebugs
const int DOODLEBUG = 1;
const int ANT = 2;

//Values for counter when determining if ants or doodles should breed
const int ANT_BREED = 3; //3 lifespans
const int DOODLE_BREED = 8; //8 lifespans

//value for counter to determine of a doodle should starve
const int DOODLE_STARVE = 3; //3 lifespans

//This was causing many errors, had to look up on stackoverflow
//source: http://stackoverflow.com/questions/4757565/c-forward-declaration
class Organism;
class Doodlebug;
class Ant;
/*********************************************************************
 ** Description: Implementation for Ant class
 *********************************************************************/
/*********************************************************************
 ** Constructor: default
 ** Description: uses the default constructor from organism to create
 ** a default ant
 ** Parameters: none
 *********************************************************************/
Ant::Ant() : Organism() {
	//inentionally left blank
}

/*********************************************************************
 ** Constructor: overloaded
 ** Description: Creates an ant object in world array by using the
 ** overloaded constructor in organism.
 ** Parameters: World *world, int x, int y
 *********************************************************************/
Ant::Ant(World *world, int x, int y) : Organism(world,x,y) {
	//intentionally left blank
}

/*********************************************************************
 ** Function: starve
 ** Description: Always returns false, because ants never starve, Only
 ** Doodlebugs do.
 ** Parameters: none
 *********************************************************************/
bool Ant::starve() {
	return false; //never starves
}

/*********************************************************************
 ** Function: move
 ** Description: Redefined the pure virtual function from organism to
 ** reflect ant's behavior in regards to move. Randomly selects a direction
 ** 0, 1, 2, 3 for up, down, left, right. If empty (NULL) then it moves
 ** the ant from prvious cell to new cell, and sets old sell to NULL.
 ** Parameters: none
 *********************************************************************/
void Ant::move() {

	int moveDirection = rand() % 4; //generates 0, 1, 2, 3

	// Try to move up, if not at an edge and empty spot
	if (moveDirection == 0) {
		if ((y > 0) && (world->getFromWorld(x, y-1) == NULL)) {
			world->setInWorld(x, y-1, world->getFromWorld(x, y));  // Move to new spot
			world->setInWorld(x, y, NULL);
			//enusre ant has correct coordinate y now
			y--;
		}
	}
	// Try to move down
	else if (moveDirection == 1) {
		if ((y < MWS-1) && (world->getFromWorld(x, y+1) == NULL)) {
			world->setInWorld(x, y+1, world->getFromWorld(x, y));  // Move to new spot
			world->setInWorld(x, y, NULL);  // Set current spot to empty
			y++;
		}
	}
	// Try to move left
	else if (moveDirection == 2) {
		if ((x > 0) && (world->getFromWorld(x-1, y) == NULL)) {
			world->setInWorld(x-1, y, world->getFromWorld(x, y));  // Move to new spot
			world->setInWorld(x, y, NULL);  // Set current spot to empty
			x--;
		}
	}
	// Try to move right
	else {
		if ((x < MWS-1) && (world->getFromWorld(x+1, y) == NULL)) {
			world->setInWorld(x+1, y, world->getFromWorld(x, y));  // Move to new spot
			world->setInWorld(x, y, NULL);  // Set current spot to empty
			x++;
		}
	}
}

/*********************************************************************
 ** Function: getType
 ** Description: Redefined the pure virtual function from organism to
 ** return the const integer value representing ANT.
 ** Parameters: none
 *********************************************************************/
int Ant::getType() {
	return ANT;
}

/*********************************************************************
 ** Function: breed
 ** Description: Redefined the pure virtual function from organism to
 ** create a new ant if, the ant in question survives 3 lifespans. It
 ** won't breed if there is not an open spot. My choice to check down,
 ** then up, then left, then right.
 ** Parameters: none
 *********************************************************************/
void Ant::breed() {
	//increment lifespans every time the function is called
	lifespans++;

	//check to see if the ant has survived enough lifespans to breed (3)
	if (lifespans == ANT_BREED) {

		//reset to 0 if it is ready to breed
		lifespans = 0;

		if ((y > 0) && (world->getFromWorld(x, y-1) == NULL)) {
			/*Ant *spawn =*/  new Ant(world, x, y-1);
		}
		//checking to ensure not off map
		else if ((y < MWS-1) && (world->getFromWorld(x, y+1) == NULL)) {
			/*Ant *spawn =*/  new Ant(world, x, y+1);
		}
		else if ((x > 0) && (world->getFromWorld(x-1, y) == NULL)) {
			/*Ant *spawn =*/ new Ant(world, x-1, y);
		}
		//checking to ensure not off map
		else if ((x < MWS-1) && (world->getFromWorld(x+1, y) == NULL)) {
			/*Ant *spawn =*/ new Ant(world, x+1, y);
		}
	}
}
Ant::~Ant(){

}
