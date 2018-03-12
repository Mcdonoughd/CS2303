/*
 * main.cpp
 *
 *  Created on: October 11, 2017
 *      Author: Dan M & Surya V.
 */
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
//starting values for ants and doodlebugs
//values for returning Ants and Doodlebugs
const int DOODLEBUG = 1;
const int ANT = 2;
//Values for counter when determining if ants or doodles should breed
const int ANT_BREED = 3; //3 lifespans
const int DOODLE_BREED = 8; //8 lifespans
//value for counter to determine of a doodle should starve
const int DOODLE_STARVE = 3; //3 lifespans
//forward referencing to prevent errors
class Organism;
class Doodlebug;
class Ant;

int DWS = 20; //Desired World Size
int STARTING_ANTS= 100; //Starting Number of Ants
int STARTING_DOODLES = 5; //Starting Number of DoodleBugs
int TIME_STEPS = 1000; //Number of Iterations to go
int SEED =1 ; //RNG Seed
int PAUSE = 0; //should the user have to press N between each time_step (0<true, False<=0)
//variables for replaying game
bool gameOver = false;
string userInput = "none yet";
int BIRTH_ANTS=0;//Number of Ants birthed in sim
int BIRTH_DOODLEBUGS=0;//Number of doodlebugs in sim
//create a world object gWorld (game world) (constructs an array of pointers to organism objects)
World gWorld;
/**
 * Output:
 *  prints out the required termination defined as:
 *  the original command line as represented by argv,
 *  the number of steps simulated,
 *  the total number of ants during the course of the simulation and the number remaining,
 *  the total number of doodlebugs in the course of the simulation and the number remaining,
 * 	a picture of the final grid. (as gWorld is defined after this declaration gWorld.Printworld() will just be called after this function call)
 * 	@param i
 */
void Output(int i){
	printf("Desired World Size: %d\n",DWS);
	printf("Starting Number of Ants: %d\n",STARTING_ANTS);
	printf("Starting Number of Doodlebugs: %d\n",STARTING_DOODLES);
	printf("Number of Steps: %d\n",TIME_STEPS);
	printf("Random Seed: %d\n",SEED);
	printf("PAUSE STATE: %d\n",PAUSE);
	printf("Steps Simulated: %d\n",i);
	printf("Total Number of Ants: %d\n",(STARTING_ANTS+BIRTH_ANTS));
	printf("Remaining Number of Ants: %d\n", gWorld.numAnts());
	printf("Total Number of Doodlebugs: %d\n",(STARTING_DOODLES+BIRTH_DOODLEBUGS));
	printf("Remaining Number of Doodlebugs: %d\n",gWorld.numDoodles());
	printf("Final Grid:\n");
	gWorld.PrintWorld();
}


/**
 * Main takes the input arguments and sets default parameters for running the program, then runs the program
 * @param argc
 * @param argv
 * @return
 */
int main(int argc,char *argv[]) {
	if (argc == 2){
		DWS = atoi(argv[1]);
	}
	else if(argc == 3){
		DWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
	}
	else if(argc == 4){
		DWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
	}
	else if(argc == 5){
		DWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
	}
	else if(argc == 6){
		DWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
		SEED = atoi(argv[5]);
	}
	else {}
	//seed the timer for generating random numbers
	srand(SEED);
	//directions and description
	cout << "** Hello and welcome to Ants and Doodlebugs simulation WITH randomized movement **" << endl;
	cout << "\n";
	cout << "** Here is a brief description of the rules:" << endl;
	cout << "**	1. Time is stimulated in steps and every step the ants and Doodlebugs " << endl;
	cout << "**	   perform some actions in this order:" << endl;
	cout << "**		DoodleBugs:" << endl;
	cout << "**		  MOVE - Eat bordering ants or randomly up, down, left, or right" << endl;
	cout << "**		  STARVE - If they have not eaten an ant in 3 time steps" << endl;
	cout << "**		  BREED - If they have an adjacent open cell and survive 8 time steps" << endl;
	cout << "**		Ants:" << endl;
	cout << "**		  MOVE - Randomly up, down, left, or right" << endl;
	cout << "**		  BREED - If they have an adjacent open cell and survive 3 time steps" << endl;
	cout << "\n";


	//Populates World
	gWorld.Fill(STARTING_ANTS,STARTING_DOODLES);
	if(PAUSE > 0){

		//keep track of number of steps
		for(int p=0; p<TIME_STEPS; p++){
			if(gWorld.empty()){
				gWorld.PrintWorld(); //print the empty board
				gameOver = true;
				cout << "The Game has Ended" << endl;
				Output(p);
				return 0;
			}
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
				cout << "The Game has Ended" << endl;
				Output(p);
				return 0;

			}
		}
		gameOver = true;
		cout << "The Game has Ended" << endl;
		Output(TIME_STEPS);
		return 0;
	}
	else{
		//print the world array to the console
		gWorld.PrintWorld();
		for(int p=0; p<TIME_STEPS; p++){
			if(gWorld.empty()){
				gameOver = true;
				cout << "The Game has Ended" << endl;
				Output(p);
				return 0;
			}
			//run 1 lifetime (1 step)
			gWorld.RunTheGame();
			gWorld.PrintWorld();
		}
		gameOver = true;
		cout << "The Game has Ended" << endl;
		Output(TIME_STEPS);
		return 0;
	}

	return 0;
}

