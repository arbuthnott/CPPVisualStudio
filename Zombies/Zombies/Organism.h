// Header file for class Organism
// superclass for all movable entities in the city class.

#include "Point.h"
#include <vector>

#ifndef ORGANISM_H
#define ORGANISM_H

class City;

class Organism
{
protected:
	int turnCounter;
	Point point;

	enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

public:
	// constants
	static const int ZOMBIE = 1;
	static const int HUMAN = 2;

	// constructors and destructors
	Organism();
	Organism(int width, int height);
	Organism(Point pt);
	virtual ~Organism();

	virtual int incrTurnCounter() = 0; // have to override this in subclasses.
	virtual int getSpecies() = 0; // override in subclasses.

	void setPosition(int x, int y);
	void setPosition(Point pt);
	int getRow();
	int getCol();
	Point getPoint();
};

#endif

