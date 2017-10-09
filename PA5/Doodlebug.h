

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
