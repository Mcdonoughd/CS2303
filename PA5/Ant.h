/*
 * Ant.h
 *
 *  Created on: October 11, 2017
 *      Author: Dan M & Surya V.
 */

using namespace std;

/*
 * Ant class represents an Ant
 */
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


