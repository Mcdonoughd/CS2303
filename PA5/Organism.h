/*
 * Organism.h
 *
 *  Created on: October 11, 2017
 *      Author: Dan M & Surya V.
 */

/*
 * Organism class represents both Ants and Doodlebugs
 */
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
