/*
 * World.h
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
using namespace std;
class Organism;
class Doodlebug;
class Ant;
const int MWS = 1000;
//Class world represents the board
class World {
	//these friend classes can set cells in the world
	friend class Organism;
	friend class Doodlebug;
	friend class Ant;

public:
	//constructor
	World();
	//function for printing the world to the console
	void PrintWorld();
	void RunTheGame();
	//function checking if board is empty
	bool empty();
	//functions for setting and getting organism in the array
	Organism* getFromWorld(int x, int y);	//
	void setInWorld(int x, int y, Organism *theOrganism);
	void Fill(int STARTING_ANTS,int STARTING_DOODLES);
	int numAnts();
	int numDoodles();
	~World();
private:
	//2D array of pointers towards organism class
	Organism* pGrid[MWS][MWS];
};
