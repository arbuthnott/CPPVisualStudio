// Implementation of class Organism

#include "Organism.h"
using namespace std;

// constructors and destructor
Organism::Organism() {
}
Organism::Organism(int width, int height) {
}
Organism::~Organism() {
	point.~Point();
}

// Position setters and getters
void Organism::setPosition(int row, int col) {
	point.setRow(row);
	point.setCol(col);
}
void Organism::setPosition(Point pt) {
	point.setRow(pt.getRow());
	point.setCol(pt.getCol());
}
int Organism::getRow() {
	return point.getRow();
}
int Organism::getCol() {
	return point.getCol();
}
Point Organism::getPoint() {
	return point;
}


