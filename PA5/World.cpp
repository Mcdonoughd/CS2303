

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
 ** Description: Implementation for World class
 *********************************************************************/
/*********************************************************************
 ** Constructor: default
 ** Description: fills organism array with NULL values
 ** Parameters: none
 *********************************************************************/
World::World() {
	//fill the word with null objects (empty spaces)
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			pGrid[i][j] = NULL; //fills organism array (in world class) with null values
		}
	}
}





void World::Fill(int STARTING_ANTS,int STARTING_DOODLES,int DWS){

	//integers for initial values of ants and doodlebugs for random filling of world
	int numberOfAnts = 0;
	int numberOfDoodles = 0;
	//fill the world with 100 ants
	while (numberOfAnts < STARTING_ANTS) {
		//generate a random x and y coordinate
		int x = rand() % DWS;
		int y = rand() % DWS;
		//if said coordinate is empty
		if (this->getFromWorld(x,y) == NULL) {
			//increase the counter
			numberOfAnts++;
			//create a pointer to Ant object
			/*	Ant *pAnt = */new Ant(this, x, y);
		}
	}

	//fill the world with 5 Doodlebugs
	while (numberOfDoodles < STARTING_DOODLES) {
		//generate a random x and y coordinate within desired world size
		int x = rand()%DWS;
		int y = rand()%DWS;
		//if said coordinate is empty
		if (this->getFromWorld(x,y) == NULL) {
			//increase the counter
			numberOfDoodles++;
			//create a pointer to Doodle object
			new Doodlebug(this, x, y);
		}
	}
}

/*********************************************************************
 ** Function: getFromWorld
 ** Description: returns whatever organism that is stored in the cell
 ** at coordinates x and y of the array.
 ** Parameters: int x, int y
 *********************************************************************/
Organism* World::getFromWorld(int x, int y) {
	//check to make sure in the bounds of the world
	if ((x >= 0) && (x < MWS) && ( y >= 0) && (y < MWS)) {
		return pGrid[x][y];
	}
	return NULL;
}

/*********************************************************************
 ** Function: setInWorld
 ** Description: Fills the cell at coordinates x and y with an object
 ** (pointer) from the organism (derived) class
 ** Parameters: int x, int y, Organism *theOrganism
 *********************************************************************/
void World::setInWorld(int x, int y, Organism *theOrganism) {
	//check to make sure in the bounds of the world
	if ((x >= 0) && (x < MWS) && (y >= 0) && (y < MWS)) {
		pGrid[x][y] = theOrganism;
	}
}

/*********************************************************************
 ** Function: PrintWorld
 ** Description: Prints the world to the console using O for ants and
 ** X for doodlebugs.
 ** Parameters: none
 *********************************************************************/
void World::PrintWorld() {
	//free up some space between generations
	cout << "\n";
	//print the array
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			//if no object is present output a blank space
			if (pGrid[i][j] == NULL) {
				cout << " " << "|"; // | just for formatting, easier to see cells
			}
			//if a doodlebug is there (1) output an x
			else if (pGrid[i][j]->getType() == DOODLEBUG) {
				cout << "X" << "|";
			}
			else {
				cout << "O" << "|"; //for ants
			}
		}
		cout << "\n"; //break after each row
	}
}

/*********************************************************************
 ** Function: RunTheGame
 ** Description: (1) Resets all organism so itMoved is false in the
 ** world (2) Loop through the world and move the Doodlebugs and set
 ** them as "having itMoved" if they moved (3) Do the same thing for ants
 ** (4) Check for starving doodlebugs and kill them off (5) check the
 ** bool for breeding and breed if they can. It is important to note the
 ** itMoved variable. Since we are looping from top down, this ensures
 ** that one organism doesnt move multiple times in one turn. Once it
 ** gets pinged as having moved, it wont again.
 ** Parameters: none
 *********************************************************************/
void World::RunTheGame() {

	//create a new vector and fill it with 0 - 399, each number corresponds to a cell in the world
	vector <int> randomTable;
	for(int i = 0; i < 400; i++) {
		randomTable.push_back(i);
	}

	// using built-in random generator, shuffle the vector so its in a random order
	//http://www.cplusplus.com/reference/algorithm/random_shuffle/
	random_shuffle(randomTable.begin(), randomTable.end());


	//(1) First reset all organisms so none of them have moved
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			if (pGrid[i][j] != NULL) {
				pGrid[i][j]->itMoved = false;
			}
		}
	}

	//NEW CODE
	//random selection of ant/doodle for movement
	for(vector<int>::iterator z = randomTable.begin(); z != randomTable.end(); ++z) {

		int i = *z / 20; //for row
		int j = *z % 20; //for column

		if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == DOODLEBUG)) {
			if (pGrid[i][j]->itMoved == false) { //if they haven't moved
				pGrid[i][j]->itMoved = true; // Mark as itMoved
				pGrid[i][j]->move(); //move the doodlebugs! aka eat
			}
		}

		if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == ANT)) {
			if (pGrid[i][j]->itMoved == false) {
				pGrid[i][j]->itMoved = true; // Mark as itMoved
				pGrid[i][j]->move();
			}
		}
	}


	//(4) Loop through the world to check for starving doodlebugs
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == DOODLEBUG)) { //if doodlebug
				if (pGrid[i][j]->starve()) { //if starving
					delete (pGrid[i][j]); //then kill of that doodlebug
					pGrid[i][j] = NULL; //and replace with an empty space
				}
			}
		}
	}

	//(5) Loop through the world and check for breeding
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			//make sure the organism moved
			if ((pGrid[i][j] != NULL) && (pGrid[i][j]->itMoved == true)) {
				pGrid[i][j]->breed(); //breed that organism (if it can)
			}
		}
	}

}
World::~World(){

}
