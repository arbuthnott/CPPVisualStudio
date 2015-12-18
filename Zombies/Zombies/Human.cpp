// Implementation of class Human

#include "Human.h"
using namespace std;

// Constructors and destructor
Human::Human()
{
	point = Point();
	turnCounter = 0;
}
Human::Human(int row, int col) {
	point = Point(row, col);
	turnCounter = 0;
}
Human::Human(Point pt) {
	point = pt;
	turnCounter = 0;
}
Human::~Human() {
	point.~Point();
}

// check equality by checking if the humans occupy the same point.
bool Human::operator==(Human otherHuman) {
	return (point == otherHuman.point);
}

// increment 0->1->2->0->1... whether human recruits or not.
int Human::incrTurnCounter() {
	turnCounter = (turnCounter + 1) % 3;
	return turnCounter;
}

int Human::getSpecies() {
	return Organism::HUMAN;
}
