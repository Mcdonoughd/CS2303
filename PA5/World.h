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
	void Fill(int STARTING_ANTS,int STARTING_DOODLES);
	~World();
private:
	//2D array of pointers towards organism class
	Organism* pGrid[MWS][MWS];
};
