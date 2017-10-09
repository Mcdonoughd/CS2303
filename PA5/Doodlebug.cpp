
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

/*********************************************************************
 ** Description: Implementation for Doodlebug class
 *********************************************************************/
/*********************************************************************
 ** Constructor: default
 ** Description: uses the default constructor from organism to create
 ** a default Doodlebug. Sets moveUntilStarve to 0.
 ** Parameters: none
 *********************************************************************/
Doodlebug::Doodlebug() : Organism() {
	movesUntilStarve = 0;
}

/*********************************************************************
 ** Constructor: overloaded
 ** Description: uses the overloaded constructor from organism to create
 ** an overloaded Doodlebug. Sets moveUntilStarve to 0.
 ** Parameters: none
 *********************************************************************/
Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world, x, y) {
	movesUntilStarve = 0;
}

/*********************************************************************
 ** Function: move
 ** Description: Redefined the pure virtual function from organism to
 ** reflect Doodlenbug's behavior in regards to move. First it scans up,
 ** down, left, then right to look for an ant. As soon as one is found
 ** the Doodlebug kills the ant (ant cell deleted) and moves to that
 ** spot. moveUntilStarve resets if this happens
 ** Parameters: none
 *********************************************************************/
void Doodlebug::move() {

	//if, else if statements for if the Doodlebug can eat an ant
	if ((y > 0) && (world->getFromWorld(x, y-1) != NULL) && (world->getFromWorld(x, y-1)->getType() == ANT)) {
		//delete the ant object from the world
		delete (world->pGrid[x][y-1]);
		//move "this" doodlebug to the spot the ant was in
		world->pGrid[x][y-1] = this;
		//set the spot the doodlebug just left to NULL (empty)
		world->setInWorld(x, y, NULL);
		//reset the movesUntilStarve counter
		movesUntilStarve = 0;
		//ensure y coordinate is decremented (moved up) changed for Doodlebug
		y--;
		return;
	}
	//similar algorithm below for eating down, left and right
	else if ((y < MWS-1) && (world->getFromWorld(x, y+1) != NULL) && (world->getFromWorld(x, y+1)->getType() == ANT)) {
		delete (world->pGrid[x][y+1]);
		world->pGrid[x][y+1] = this;
		world->setInWorld(x, y, NULL);
		movesUntilStarve = 0;
		y++;
		return;
	}
	//eat left
	else if ((x > 0) && (world->getFromWorld(x-1, y) != NULL) && (world->getFromWorld(x-1, y)->getType() == ANT)) {
		delete (world->pGrid[x-1][y]);
		world->pGrid[x-1][y] = this;
		world->setInWorld(x, y, NULL);
		movesUntilStarve = 0;
		x--;
		return;
	}
	//eat right
	else if ((x < MWS-1) && (world->getFromWorld(x+1, y) != NULL) && (world->getFromWorld(x+1, y)->getType() == ANT)) {
		delete (world->pGrid[x+1][y]);
		world->pGrid[x+1][y] = this;
		world->setInWorld(x, y, NULL);
		movesUntilStarve = 0;
		x++;
		return;
	}

	//Doodlebug can't eat an ant so it tries to move randomly (copied code from ant move)
	int moveDirection = rand() % 4; //values 0, 1, 2, 3

	if (moveDirection == 0) {
		if ((y > 0) && (world->getFromWorld(x, y-1) == NULL)) {
			//move the doodle to this spot
			world->setInWorld(x, y-1, world->getFromWorld(x,y));
			//set the old spot to NULL
			world->setInWorld(x, y, NULL);
			//ensure the y coordinate for object is decremented to reflect new cell
			y--;
		}
	}
	//attempt to move down
	else if (moveDirection==1) {
		if ((y < MWS-1) && (world->getFromWorld(x, y+1) == NULL)) {
			world->setInWorld(x, y+1, world->getFromWorld(x, y));
			world->setInWorld(x, y, NULL);
			y++;
		}
	}
	//attempt to move left
	else if (moveDirection == 2) {
		if ((x > 0) && (world->getFromWorld(x-1, y) == NULL)) {
			world->setInWorld(x-1, y, world->getFromWorld(x, y));
			world->setInWorld(x, y, NULL);
			x--;
		}
	}
	//attempt to move right
	else {
		if ((x < MWS-1) && (world->getFromWorld(x+1, y) == NULL)) {
			world->setInWorld(x+1, y, world->getFromWorld(x, y));
			world->setInWorld(x, y, NULL);
			x++;
		}
	}
	//if the Doodlebug could not eat anything, increment the counter
	movesUntilStarve++;
}

/*********************************************************************
 ** Function: getType
 ** Description: Redefined the pure virtual function from organism to
 ** return the const integer value representing DOODLEBUG.
 ** Parameters: none
 *********************************************************************/
int Doodlebug::getType() {
	return DOODLEBUG;
}

/*********************************************************************
 ** Function: breed
 ** Description: Redefined the pure virtual function from organism to
 ** create a new doodlebug if, the doodlebug in question survives 8 lifespans.
 ** It won't breed if there is not an open spot. My choice to check down,
 ** then up, then left, then right.
 ** Parameters: none
 *********************************************************************/
void Doodlebug::breed() {

	//increase the lifespans of the Doodlebug
	lifespans++;

	//if Doodlebug has survived 8 lifespans
	if (lifespans == DOODLE_BREED) {
		//reset the lifespan counter
		lifespans = 0;

		//above
		if ((y > 0) && (world->getFromWorld(x, y-1) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(world, x, y-1);
		}
		//left
		else if ((y < MWS-1) && (world->getFromWorld(x, y+1) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(world, x, y+1);
		}
		//right
		else if ((x > 0) && (world->getFromWorld(x-1, y) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(world, x-1, y);
		}
		//down
		else if ((x < MWS-1) && (world->getFromWorld(x+1, y) == NULL)) {
			/*Doodlebug *newDoodle =*/ new Doodlebug(world, x+1, y);
		}
	}
}

/*********************************************************************
 ** Function: starve
 ** Description: Redefined the pure virtual function starve from abstract
 ** class Organism to return true if a Doodlebug has not eaten in 3
 ** turns and false if they have. Use the movesUntilStarve private
 ** variable to determine this.
 ** Parameters: none
 *********************************************************************/
bool Doodlebug::starve() {
	//starve
	if (movesUntilStarve > DOODLE_STARVE) {
		return true;
	}
	//survive
	else {
		return false;
	}
}
Doodlebug::~Doodlebug(){

}
