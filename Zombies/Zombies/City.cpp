// implementation file for class City
#include "City.h"
#include "Organism.h"
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include <iostream>
using namespace std;

/////////////////////////////////////////////////
// CONSTRUCTOR, DESTRUCTOR, GETTERS
/////////////////////////////////////////////////
City::City() {}
City::~City() {
	for (unsigned int idx = 0; idx < zombies.size(); idx++) {
		delete zombies[idx];
	}
	for (unsigned int idx = 0; idx < humans.size(); idx++) {
		delete humans[idx];
	}
}
vector<Human*> City::getHumans() {
	return humans;
}
vector<Zombie*> City::getZombies() {
	return zombies;
}
bool City::stillAlive() {
	return zombies.size() > 0 && humans.size() > 0;
}

///////////////////////////////////////////////////////////
// ADD/REMOVE ZOMBIES OR HUMANS
///////////////////////////////////////////////////////////

// add an organism to either the zombies or humans vector.
void City::addOrganism(Organism* org) {
	if (org->getSpecies() == Organism::HUMAN) {
		Human *human = dynamic_cast<Human*>(org);
		humans.push_back(human);
	}
	else if (org->getSpecies() == Organism::ZOMBIE) {
		Zombie *zombie = dynamic_cast<Zombie*>(org);
		zombies.push_back(zombie);
	}
}

// add a new human at input point
void City::addHuman(Point pt) {
	Human* human = new Human(pt);
	humans.push_back(human);
}

// add a new zombie at input point
void City::addZombie(Point pt) {
	Zombie* zombie = new Zombie(pt);
	zombies.push_back(zombie);
}

// remove by value from either zombies or humans vector. BY VALUE
// try to delete the organism.
void City::removeOrganism(Organism* org) {
	if (org->getSpecies() == Organism::HUMAN) {
		Human* h = dynamic_cast<Human*>(org);
		for (int idx = 0; idx < humans.size(); idx++) {
			if (*h == *humans[idx]) {
				humans.erase(humans.begin() + idx);
				delete org;
				break;
			}
		}
	}
	else if (org->getSpecies() == Organism::ZOMBIE) {
		Zombie* z = dynamic_cast<Zombie*>(org);
		for (int idx = 0; idx < zombies.size(); idx++) {
			if (*z == *zombies[idx]) {
				zombies.erase(zombies.begin() + idx);
				delete org;
				break;
			}
		}
	}
}

// remove organism at input location.  BY LOCATION
void City::removeOrganism(Point pt) {
	for (int idx = 0; idx < humans.size(); idx++) {
		if (humans[idx]->getPoint() == pt) {
			Human* h = humans[idx];
			humans.erase(humans.begin() + idx);
			delete h;
			break;
		}
	}
	for (int idx = 0; idx < zombies.size(); idx++) {
		if (zombies[idx]->getPoint() == pt) {
			Zombie* z = zombies[idx];
			zombies.erase(zombies.begin() + idx);
			delete z;
			break;
		}
	}
}

void City::addRandomHuman() {
	if (zombies.size() + humans.size() >= (GRID_HEIGHT) * (GRID_WIDTH) - 1) {
		return; // avoid looking for sparse random locations.
	}
	srand(time(NULL));
	vector<vector<char>> grid = getGrid();
	int row = rand() % GRID_HEIGHT;
	int col = rand() % GRID_WIDTH;
	while (grid[row][col] != SPACE_CHAR) {
		row = rand() % GRID_HEIGHT;
		col = rand() % GRID_WIDTH;
	}
	addHuman(Point(row, col));
}

void City::addRandomZombie() {
	if (zombies.size() + humans.size() >= (GRID_HEIGHT) * (GRID_WIDTH) - 1) {
		return; // avoid looking for sparse random locations.
	}
	srand(time(NULL));
	vector<vector<char>> grid = getGrid();
	int row = rand() % GRID_HEIGHT;
	int col = rand() % GRID_WIDTH;
	while (grid[row][col] != SPACE_CHAR) {
		row = rand() % GRID_HEIGHT;
		col = rand() % GRID_WIDTH;
	}
	addZombie(Point(row, col));
}

////////////////////////////////////////////////////////////////////
// GET CHAR GRID AND TOSTRING METHODS
////////////////////////////////////////////////////////////////////

// return array consisting of X, O, or _ depending on zombie, human, or empty.
vector<vector<char>> City::getGrid() {
	// fill a grid with the empty char
	vector<vector<char>> grid(GRID_HEIGHT, vector<char>(GRID_WIDTH, '_'));
	for (unsigned int row = 0; row < GRID_HEIGHT; row++) {
		for (unsigned int col = 0; col < GRID_WIDTH; col++) {
			grid[row][col] = City::SPACE_CHAR;
		}
	}
	for (unsigned int idx = 0; idx < zombies.size(); idx++) {
		Zombie* z = zombies[idx];
		grid[z->getRow()][z->getCol()] = City::ZOMBIE_CHAR;
	}
	for (unsigned int idx = 0; idx < humans.size(); idx++) {
		Human* h = humans[idx];
		grid[h->getRow()][h->getCol()] = City::HUMAN_CHAR;
	}
	return grid;
}

// Returns a (color free) version of the output.
string City::toString() {
	vector<vector<char>> grid = getGrid();
	string retString = "";
	for (unsigned int row = 0; row < GRID_HEIGHT; row++) {
		for (unsigned int col = 0; col < GRID_WIDTH; col++) {
			retString += grid[row][col];
			if (col < GRID_WIDTH - 1) {
				retString += " ";
			}
		}
		retString += "\n";
	}
	return retString;
}

// Output grid, with colors.
ostream& operator<<(ostream &output, City &city) {
	// modify the toString method to add in colors.
	vector<vector<char>> grid = city.getGrid();
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (unsigned int row = 0; row < GRID_HEIGHT; row++) {
		for (unsigned int col = 0; col < GRID_WIDTH; col++) {
			char chr = grid[row][col];
			if (chr == City::ZOMBIE_CHAR) {
				SetConsoleTextAttribute(hstdout, 0xC);
			}
			else if (chr == City::HUMAN_CHAR) {
				SetConsoleTextAttribute(hstdout, 0xB);
			}
			output << chr;
			SetConsoleTextAttribute(hstdout, 0xF);
			if (col < GRID_WIDTH - 1) {
				output << " ";
			}
		}
		output << endl;
	}
	return output;
}

//////////////////////////////////////////////////////////////////
// ITERATE AND ITS HELPER METHODS
//////////////////////////////////////////////////////////////////

// run one move interation.
void City::iterate() {
	// for each zombie in the list, try to eat. If impossible, try to move.
	for (unsigned int idx = 0; idx < zombies.size(); idx++) {
		if (!tryEat(zombies[idx])) {
			tryMove(zombies[idx]);
			zombies[idx]->incrHunger();
		}
	}

	// for each human, try to move.
	for (unsigned int idx = 0; idx < humans.size(); idx++) {
		tryMove(humans[idx]);
	}

	// have zombies try to convert.
	int sizeCap = zombies.size(); // this prevents newly pushed zombies from being iterated over.
	for (unsigned int idx = 0; idx < sizeCap; idx++) {
		if (tryConvert(zombies[idx])) {
			zombies[idx]->resetTurnCounter();
		}
	}

	// have humans try to recruit
	sizeCap = humans.size(); // this prevents newly recruited humans from being iterated over.
	for (unsigned int idx = 0; idx < sizeCap; idx++) {
		tryRecruit(humans[idx]);
	}

	// check for zombie death from hunger / conversion to human.
	// Have to be clever so I don't update the zombies vector while iterating over it.
	vector<Zombie*> starvedZombies = getStarvedZombies();
	for (unsigned int idx = 0; idx < starvedZombies.size(); idx++) {
		Point pt = starvedZombies[idx]->getPoint();
		removeOrganism(starvedZombies[idx]);
		addHuman(pt);
	}
}

bool City::tryEat(Zombie* zombie) {
	// look for nearby humans.
	for (unsigned int idx = 0; idx < humans.size(); idx++) {
		if (zombie->getPoint().isNear(humans[idx]->getPoint())) {
			// eat that human
			zombie->setPosition(humans[idx]->getPoint());
			removeOrganism(humans[idx]);
			zombie->resetHunger();
			return true;
		}
	}
	// nobody near to eat.
	return false;
}

void City::tryMove(Organism* org) {
	// create a list of possible moves.
	Point pt = org->getPoint();
	vector<Point> moves = getVacantAdjacent(pt);
	// choose a move and make it (if any)
	if (moves.size() > 0) {
		srand(time(NULL));
		int moveIdx = rand() % moves.size();
		org->setPosition(moves[moveIdx]);
	}
}

bool City::tryConvert(Zombie* zombie) {
	int ctr = zombie->incrTurnCounter();
	if (ctr >= 8) {
		// look for nearby humans.
		for (unsigned int idx = 0; idx < humans.size(); idx++) {
			if (zombie->getPoint().isNear(humans[idx]->getPoint())) {
				// convert that human
				Point pt = humans[idx]->getPoint();
				removeOrganism(pt);
				addZombie(pt);
				return true;
			}
		}
	}
	// didn't convert anybody.
	return false;
}

void City::tryRecruit(Human* human) {
	int ctr = human->incrTurnCounter();
	if (ctr == 0) {
		// look for possible recruit locations.
		vector<Point> moves = getVacantAdjacent(human->getPoint());
		if (moves.size() > 0) {
			srand(time(NULL));
			int moveIdx = rand() % moves.size();
			addHuman(moves[moveIdx]);
		}
	}
}

// Some Helper methods:

// Check for expired hunger counters
vector<Zombie*> City::getStarvedZombies() {
	vector<Zombie*> hungryZombies;
	for (unsigned int idx = 0; idx < zombies.size(); idx++) {
		int ctr = zombies[idx]->getHunger();
		if (ctr >= 3) {
			hungryZombies.push_back(zombies[idx]);
		}
	}
	return hungryZombies;
}

// return a list of vacant points adjacent (non-diagonal) to input point.
vector<Point> City::getVacantAdjacent(Point pt) {
	vector<vector<char>> grid = getGrid();
	vector<Point> moves;
	if (pt.getRow() > 0 && grid[pt.getRow() - 1][pt.getCol()] == City::SPACE_CHAR) { // North
		moves.push_back(Point(pt.getRow() - 1, pt.getCol()));
	}
	if (pt.getRow() < GRID_HEIGHT - 1 && grid[pt.getRow() + 1][pt.getCol()] == City::SPACE_CHAR) { // South
		moves.push_back(Point(pt.getRow() + 1, pt.getCol()));
	}
	if (pt.getCol() > 0 && grid[pt.getRow()][pt.getCol() - 1] == City::SPACE_CHAR) { // West
		moves.push_back(Point(pt.getRow(), pt.getCol() - 1));
	}
	if (pt.getCol() < GRID_WIDTH - 1 && grid[pt.getRow()][pt.getCol() + 1] == City::SPACE_CHAR) { // East
		moves.push_back(Point(pt.getRow(), pt.getCol() + 1));
	}
	return moves;
}