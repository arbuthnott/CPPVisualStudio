// Header file for class Human

#include "Organism.h"

#ifndef HUMAN_H
#define HUMAN_H

class City;

class Human : public Organism
{
public:
	Human();
	Human(int x, int y);
	Human(Point pt);
	virtual ~Human();

	int incrTurnCounter();
	int getSpecies();
	bool operator==(Human otherHuman);
};

#endif


