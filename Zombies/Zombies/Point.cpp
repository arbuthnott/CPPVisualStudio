// implementation of Point class

#include "Point.h"
#include <cstdlib>
using namespace std;

// Constructors and destructor
Point::Point() {
	row = 0;
	col = 0;
}
Point::Point(int r, int c) {
	row = r;
	col = c;
}
Point::~Point() {}

// getters and setters
void Point::setRow(int r) {
	row = r;
}
void Point::setCol(int c) {
	col = c;
}
int Point::getRow() {
	return row;
}
int Point::getCol() {
	return col;
}

// Points are equal if their row and column are equal
bool Point::operator==(Point otherPoint) {
	return (row == otherPoint.row && col == otherPoint.col);
}

// Returns true if input point is one grid square away, including diagonally.
bool Point::isNear(Point otherPoint) {
	return (abs(row - otherPoint.row) <= 1 &&
		abs(col - otherPoint.col) <= 1 &&
		!(*this == otherPoint));
}

// Returns true if input point is one grid square away *not* including diagonally.
bool Point::isAdjacent(Point otherPoint) {
	return (abs(row - otherPoint.row) + abs(col - otherPoint.col) == 1);
}