/*
 * main.cpp
 *
 *  Created on: Feb 26, 2017
 *      Author: student
 */

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
 ** Description: Driver function
 *********************************************************************/
int STARTING_ANTS= 100;
int STARTING_DOODLES = 5;
int TIME_STEPS = 1000;
int SEED =1 ;
int PAUSE = 0;
int main(int argc,char *argv[]) {
	//istringstream ss;
	if(argc == 1){
		MWS = 20;
		STARTING_ANTS = 100;
		STARTING_DOODLES = 5;
		TIME_STEPS = 1000;
		SEED = 1;
		PAUSE = 0;
	}
	else if (argc == 2){
		//MWS = atoi(argv[1]);
		STARTING_ANTS = 100;
		STARTING_DOODLES = 5;
		TIME_STEPS = 1000;
		SEED = 1;
		PAUSE = 0;
	}
	else if(argc == 3){
		//MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = 5;
		TIME_STEPS = 1000;
		SEED = 1;
		PAUSE = 0;
	}
	else if(argc == 4){
		//	MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = 1000;
		SEED = 1;
		PAUSE = 0;
	}
	else if(argc == 5){
		//MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
		SEED = 1;
		PAUSE = 0;
	}
	else if(argc == 6){
		MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
		SEED = atoi(argv[5]);
		PAUSE = 0;
	}
	else {
		MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
		SEED = atoi(argv[5]);
		PAUSE = atoi(argv[6]);
	}
	//seed the timer for generating random numbers
	srand(SEED);

	//directions and description
	cout << "** Hello and welcome to Ants and Doodlebugs simulation WITH randomized movement **" << endl;
	cout << "\n";
	cout << "** Here is a brief description of the rules:" << endl;
	cout << "**	1. Time is stimulated in steps and every step the ants and Doodlebugs " << endl;
	cout << "**	   perform some actions:" << endl;
	cout << "**		Ants:" << endl;
	cout << "**		  MOVE - Randomly up down left and right" << endl;
	cout << "**		  BREED - If they can to an open cell if they survive 3 time steps" << endl;
	cout << "**		DoodleBugs:" << endl;
	cout << "**		  MOVE - Eat bordering ants or randomly up down left and right" << endl;
	cout << "**		  BREED - If they can to an open cell if they survive 8 time steps" << endl;
	cout << "**		  STARVE - If they have not eaten an ant in 3 time steps" << endl;
	cout << "\n";

	//create a world object gWorld (game world) (constructs an array of pointers to organism objects)
	World gWorld;

	//integers for intiial values of ants and doodlebugs for random filling of world
	int numberOfAnts = 0;
	int numberOfDoodles = 0;

	//fill the world with 100 ants
	while (numberOfAnts < STARTING_ANTS) {
		//generate a random x and y coordinate
		int x = rand() % MWS;
		int y = rand() % MWS;
		//if said coordinate is empty
		if (gWorld.getFromWorld(x,y) == NULL) {
			//increase the counter
			numberOfAnts++;
			//create a pointer to Ant object
			/*	Ant *pAnt = */new Ant(&gWorld, x, y);
		}
	}

	//fill the world with 5 doodlebugs
	while (numberOfDoodles < STARTING_DOODLES) {
		//generate a random x and y coordinate
		int x = rand()%MWS;
		int y = rand()%MWS;
		//if said coordinate is empty
		if (gWorld.getFromWorld(x,y) == NULL) {
			//increase the counter
			numberOfDoodles++;
			//create a pointer to Ant object
			/*Doodlebug *pDoodle = */new Doodlebug(&gWorld, x, y);
		}
	}

	//variables for replaying game
	bool gameOver = false;
	string userInput = "none yet";

	if(PAUSE > 0){
	while (gameOver == false ){
			//print the world array to the console
			gWorld.PrintWorld();

			//run 1 lifetime (1 step)
			gWorld.RunTheGame();

			cout << "Enter [n] to see the next generation : Any other key to exit" << endl;
			cin >> userInput;

			if (userInput == "n") {
				//continue playing if user enters n
				gameOver = false;
			}
			else {
				//exit if user does not enter n
				gameOver = true;
			}
		}
	}
	else{

			//print the world array to the console
			gWorld.PrintWorld();
while(gameOver == false){
			for(int p=0; p<TIME_STEPS; p++){
				//run 1 lifetime (1 step)
				gWorld.RunTheGame();
				gWorld.PrintWorld();
			}
			gameOver = true;
}




	}

	return 0;
}

