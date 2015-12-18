// Implementation of class Zombie

#include "Zombie.h"
#include <algorithm>
using namespace std;

// Constructors and destructor
Zombie::Zombie() {
	point = Point(0, 0);
	turnCounter = 0;
	hungerCounter = 0;
}
Zombie::Zombie(int row, int col) {
	point = Point(row, col);
	turnCounter = 0;
	hungerCounter = 0;
}
Zombie::Zombie(Point pt) {
	point = pt;
	turnCounter = 0;
	hungerCounter = 0;
}
Zombie::~Zombie()
{
	point.~Point();
}

// check equality by checking if zombies occupy same point.
bool Zombie::operator==(Zombie otherZombie) {
	return (point == otherZombie.point);
}

// increment to a maximum of 8.  Resets done during "Convert".
int Zombie::incrTurnCounter() {
	turnCounter = min(turnCounter + 1, 8);
	return turnCounter;
}

void Zombie::resetTurnCounter() {
	turnCounter = 0;
}

// "Hunger" methods to check if zombie has eaten recently.
void Zombie::incrHunger() {
	hungerCounter++;
}
void Zombie::resetHunger() {
	hungerCounter = 0;
}
int Zombie::getHunger() {
	return hungerCounter;
}

int Zombie::getSpecies() {
	return Organism::ZOMBIE;
}
