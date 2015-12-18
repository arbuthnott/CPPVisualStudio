#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class Validator {
public:
	Validator() {}
	~Validator() {}
	string getInput() {
		string input = "";
		char currentKey;
		const static int maxLineLength = 20;

		currentKey = _getch();
		while (currentKey != 13) {
			if ((currentKey >= 32) && (currentKey <= 126)) {
				// valid character, accept and print
				if (maxLineLength > input.length()) {
					input += currentKey;
					printf("%c", currentKey);
				}
			}
			else if (currentKey == 8) {
				// backspace - change string var and erase from screen.
				if (input.length() > 0) {
					input.erase(input.length() - 1);
					printf("\b \b"); // "print" the backspace to screen.
				}
			}
			currentKey = _getch();
		}
		return input;
	} // end method getInput
}; // end class Validator

class Point {
public:
	Point(int rw, int cl) {
		this->row = rw;
		this->col = cl;
	}
	~Point() {}
	int getRow() {
		return this->row;
	}
	int getCol() {
		return this->col;
	}
private:
	int row, col;
}; // end class Point

class Board {
private:
	char entries[3][3];

public:
	const static char X = 'X';
	const static char O = 'O';
	const static char BLANK = ' ';
	Board() {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				entries[row][col] = BLANK;
			}
		}
	}
	~Board() {}
}; // end class Board

int main() {

	Board board;

	_getch();
	return 0;
}