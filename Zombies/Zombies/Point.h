// header file for Point class
// wrapper class for (row, col) coordinates.

#ifndef POINT_H
#define POINT_H

class Point
{
private:
	int row;
	int col;
public:
	// constructors and destructors
	Point();
	Point(int r, int c);
	~Point();

	// getters and setters
	void setRow(int r);
	void setCol(int c);
	int getRow();
	int getCol();

	// equality override
	bool operator==(Point otherPoint);

	// proximity detector
	bool isNear(Point otherPoint);
	bool isAdjacent(Point otherPoint);
};

#endif