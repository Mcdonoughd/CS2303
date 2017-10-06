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
using namespace std;


//Delare known constants from instructions
//constant for the world dimensions of 20x20
const int MWS = 20; //max world size

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
 ** Description: World class declaration
 *********************************************************************/
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

	//functions for setting and getting organism in the array
	Organism* getFromWorld(int x, int y);	//
	void setInWorld(int x, int y, Organism *theOrganism);
	~World();
private:
	//2D array of pointers towards organism class
	Organism* pGrid[MWS][MWS];

};


/*********************************************************************
 ** Description: Organism class declaration (abstract class)
 *********************************************************************/
class Organism {

	//Since we need to allow the world to interact with organism, make it a friend
	friend class World;

public:

	//constructors
	Organism();
	Organism(World *world, int x, int y);

	//virtual functions for breed, move and starve
	virtual void breed() = 0;
	virtual void move() = 0;
	virtual bool starve() = 0;

	//virtual function for checking if an object is an ant or doodle
	virtual int getType() = 0;
	virtual ~Organism();
protected:

	//for coordinates in the world
	int x;
	int y;

	//to check if the insect has itMoved (so 2+ moves 1 lifespan is checked)
	bool itMoved;

	//to track the time steps which determine breeding and starving
	int lifespans;

	//pointer to the world
	World *world;

};


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

/*********************************************************************
 ** Function: getFromWorld
 ** Description: retruns whatever an organism that is stored in the cell
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
 ** (pointer) from the organism (dervied) class
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
/*********************************************************************
 ** Description: Doodlebug class declaration
 *********************************************************************/
class Doodlebug : public Organism {

	friend class World;

public:

	//constructors
	Doodlebug();
	Doodlebug(World *world, int x, int y);

	//breed, move and starve methods
	void breed();
	void move();
	bool starve();

	//returns an int (constant) for doodlebug
	int getType();
	virtual ~Doodlebug();
private:

	//an int to hold how many times a doodlebug can move before starving
	int movesUntilStarve;
};

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
/*********************************************************************
 ** Description: Ant class declaration
 *********************************************************************/
class Ant : public Organism {

	friend class World;

public:

	//constructors
	Ant();
	Ant(World *world, int x, int y);

	//breed, move and starve methods
	void breed();
	void move();
	bool starve();

	//function to return the type
	int getType();
	~Ant();
};

Ant::~Ant(){

}
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
		//MWS = 20;
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
		//MWS = atoi(argv[1]);
		STARTING_ANTS = atoi(argv[2]);
		STARTING_DOODLES = atoi(argv[3]);
		TIME_STEPS = atoi(argv[4]);
		SEED = atoi(argv[5]);
		PAUSE = 0;
	}
	else {
		//MWS = atoi(argv[1]);
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

