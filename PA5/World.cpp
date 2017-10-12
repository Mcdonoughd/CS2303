/*
 * World.cpp
 *
 *  Created on: October 11, 2017
 *      Author: Dan M & Surya V.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
#include "World.h"
#include "Common.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;
//Delare known constants from instructions
//starting values for ants and doodlebugs

//values for returning Ants and Doodlebugs
const int DOODLEBUG = 1;
const int ANT = 2;

//Values for counter when determining if ants or doodles should breed
const int ANT_BREED = 3; //3 lifespans
const int DOODLE_BREED = 8; //8 lifespans

//value for counter to determine of a doodle should starve
const int DOODLE_STARVE = 3; //3 lifespans

class Organism;
class Doodlebug;
class Ant;


/**
 * Constructor:
 * fills organism array with NULL values
 */
World::World() {
	//fill the word with null objects (empty spaces)
	for (int i = 0; i < MWS; ++i) {
		for (int j = 0; j < MWS; ++j) {
			pGrid[i][j] = NULL; //fills organism array (in world class) with null values
		}
	}
}


/**
 * Fill:
 * Initializes the board with Ants and Doodlebugs at a random location
 * @param STARTING_ANTS
 * @param STARTING_DOODLES
 */
void World::Fill(int STARTING_ANTS,int STARTING_DOODLES){
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


/**
 * getFromWorld:
 * returns whatever organism that is stored in the cell
 * at coordinates x and y of the array.
 * @param x
 * @param y
 * @return
 */
Organism* World::getFromWorld(int x, int y) {
	//check to make sure in the bounds of the world
	if ((x >= 0) && (x < DWS) && ( y >= 0) && (y < DWS)) {
		return pGrid[x][y];
	}
	return NULL;
}

/**
 * setInWorld:
 * Fills the cell at coordinates x and y with an object
 * (pointer) from the organism (derived) class
 * @param x
 * @param y
 * @param theOrganism
 */
void World::setInWorld(int x, int y, Organism *theOrganism) {
	//check to make sure in the bounds of the world
	if ((x >= 0) && (x < DWS) && (y >= 0) && (y < DWS)) {
		pGrid[x][y] = theOrganism;
	}
}

/**
 * PrintWorld:
 *  Prints the world to the console using O for ants and
 *  X for doodlebugs.
 */
void World::PrintWorld() {
	//free up some space between generations
	cout << "\n";
	//print the array
	for (int i = 0; i < DWS; ++i) {
		for (int j = 0; j < DWS; ++j) {
			//if no object is present output a blank space
			if(j==0){
				cout << "|";
			}
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

/**
 * RunTheGame
 * 1) Resets all organism so itMoved is false in the
 * world (2) Loop through the world and move the Doodlebugs and set
 * them as "having itMoved" if they moved (3) Do the same thing for ants
 * (4) Check for starving doodlebugs and kill them off (5) check the
 * bool for breeding and breed if they can. It is important to note the
 * itMoved variable. Since we are looping from top down, this ensures
 * that one organism doesnt move multiple times in one turn. Once it
 * gets pinged as having moved, it wont again.
 */
void World::RunTheGame() {

	//create a new vector and fill it with 0 - 399, each number corresponds to a cell in the world
	vector <int> randomTable;
	for(int i = 0; i < (DWS*DWS); i++) {
		randomTable.push_back(i);
	}
	//Shuffle the vector so its in a random order
	random_shuffle(randomTable.begin(), randomTable.end());
	//(1) First reset all organisms so none of them have moved
	for (int i = 0; i < DWS; ++i) {
		for (int j = 0; j < DWS; ++j) {
			if (pGrid[i][j] != NULL) {
				pGrid[i][j]->itMoved = false;
			}
		}
	}

	//random selection of ant/doodle for movement
	for(vector<int>::iterator z = randomTable.begin(); z != randomTable.end(); ++z) {
		int i = *z / DWS; //for row
		int j = *z % DWS; //for column

		//Move Doodlebugs
		if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == DOODLEBUG)) {
			if (pGrid[i][j]->itMoved == false) { //if they haven't moved
				pGrid[i][j]->itMoved = true; // Mark as itMoved
				pGrid[i][j]->move(); //Move the doodlebugs! aka eat
			}
		}

		//Move Ants
		if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == ANT)) {
			if (pGrid[i][j]->itMoved == false) {
				pGrid[i][j]->itMoved = true; // Mark as itMoved
				pGrid[i][j]->move();
			}
		}
	}


	//(4) Loop through the world to check for starving doodlebugs
	for (int i = 0; i < DWS; ++i) {
		for (int j = 0; j < DWS; ++j) {
			if ((pGrid[i][j] != NULL) && (pGrid[i][j]->getType() == DOODLEBUG)) { //if doodlebug
				if (pGrid[i][j]->starve()) { //if starving
					delete (pGrid[i][j]); //then kill of that doodlebug
					pGrid[i][j] = NULL; //and replace with an empty space
				}
			}
		}
	}

	//(5) Loop through the world and check for breeding
	for (int i = 0; i < DWS; ++i) {
		for (int j = 0; j < DWS; ++j) {
			//make sure the organism moved
			if ((pGrid[i][j] != NULL) && (pGrid[i][j]->itMoved == true)) {
				pGrid[i][j]->breed(); //breed that organism (if it can)
			}
		}
	}

}



/**
 * empty:
 * returns true is all cells on the board are null
 * @return
 */
bool World::empty(){
	//Loop through the world and check for null pointers
		for (int i = 0; i < DWS; ++i) {
			for (int j = 0; j < DWS; ++j) {
				//check if board space is empthy
				if ((pGrid[i][j] != NULL)) {
					return false; //There si something still on the board
				}
			}
		}
		return true; //There is nothing on the board
}
World::~World(){

}
