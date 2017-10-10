
#include "Common.h"
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
 ** Description: Implementation for Organism class
 *********************************************************************/
/*********************************************************************
 ** Constructor: default
 ** Description: Creates a default organism
 ** Paramters: None
 *********************************************************************/
Organism::Organism() {

	x = 0;
	y = 0;

	//empty space
	world = NULL;

	//flag for moving
	itMoved = false;
	//counter for breed/death conditions
	lifespans = 0;
}

/*********************************************************************
 ** Constructor: overloaded
 ** Description: Creates an organism object which is in the world array
 ** Paramters: World *pWorld, int x, int y
 *********************************************************************/
Organism::Organism(World *pWorld, int x, int y) {

	this->x = x;
	this->y = y;

	//in reference to the world object
	this->world = pWorld;
	//sets the cell in world to object
	pWorld->setInWorld(x, y, this);

	//flag for moving
	itMoved = false;
	//counter for breed/death conditions
	lifespans = 0;
}
Organism::~Organism(){

}
