// Header file for class City
// central class for zombie apocalype simulation.

#include <iostream>
#include "Zombie.h"
#include "Human.h"
#include <vector>
#include <string>

#ifndef CITY_H
#define CITY_H

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City
{
protected:
	std::vector<Zombie*> zombies;
	std::vector<Human*> humans;

public:
	// constants
	static const char ZOMBIE_CHAR = 'X';
	static const char HUMAN_CHAR = 'O';
	static const char SPACE_CHAR = '_';

	// constructor and destructor
	City();
	~City();
	// getters and setters
	std::vector<Human*> getHumans();
	std::vector<Zombie*> getZombies();

	// check state
	bool stillAlive();

	// add/remove zombies or humans
	void addOrganism(Organism*);
	void addHuman(Point pt);
	void addZombie(Point pt);
	void removeOrganism(Organism*);
	void removeOrganism(Point pt);
	void addRandomHuman();
	void addRandomZombie();
	
	// for string output
	std::vector<std::vector<char>> getGrid();
	std::string toString();
	friend std::ostream& operator<<(std::ostream &output, City &city);

	// iteration methods
	void iterate();
	bool tryEat(Zombie* zombie);
	void tryMove(Organism* org);
	bool tryConvert(Zombie* zombie);
	void tryRecruit(Human* human);
	std::vector<Point> getVacantAdjacent(Point pt);
	std::vector<Zombie*> getStarvedZombies();
};

#endif

