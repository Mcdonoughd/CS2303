

using namespace std;

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


