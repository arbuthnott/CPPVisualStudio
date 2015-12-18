// Header file for class Zombie

#include "Organism.h"

#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie : public Organism
{
protected:
	int hungerCounter;

public:
	Zombie();
	Zombie(int x, int y);
	Zombie(Point pt);
	virtual ~Zombie();
	int getSpecies();
	bool operator==(Zombie);

	int incrTurnCounter();
	void resetTurnCounter();
	void incrHunger();
	void resetHunger();
	int getHunger();

};

#endif
