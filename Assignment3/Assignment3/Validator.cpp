// Implementation file for class Validator

#include <conio.h>
#include <iostream>
#include <string>
#include <regex>
#include "Validator.h"
using namespace std;

// Constructor and Destructor
Validator::Validator() {}
Validator::~Validator() {}

string Validator::getInput() {
	string input = "";
	char currentKey;
	const static int maxLineLength = 40;
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
	cout << endl;
	return input;
}  // end method Validator::getInput

string Validator::getName(string message) {
	cout << message;
	string input;
	input = getInput();
	string namePattern = "^([a-zA-Z\\-\\']{2,}\\s?){1,3}$";
	regex nameReg(namePattern);
	while (!regex_search(input, nameReg)) { // if no match to name pattern.
		cout << "Please enter a valid name: only letters, dashes and apostrophes are allowed." << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}

string Validator::getCourse(string message) {
	cout << message;
	string input;
	input = getInput();
	string coursePattern = "^(\\w{2,}\\s?){1,3}$";
	regex courseReg(coursePattern);
	while (false) { // replace the "false" with some "not-good-input" condition.
		cout << "Please enter a valid course: only letters and numbers are allowed." << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}

string Validator::getYN(string message) {
	cout << message;
	string input;
	input = getInput();
	while (input != "y" && input != "n") {
		cout << "Please enter only 'y' or 'n'." << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}


/** KEEPING THIS AROUND FOR REGEX REFERENCE
bool Validator::isFraction(string input) {
	string fracPattern = "^\\s*-?\\s?\\d+\\s*$|^\\s*-?\\s?\\d+\\s*\\/\\s*-?\\s?\\d+\\s*$";
	regex fracReg(fracPattern);
	return regex_search(input, fracReg);
} // end method Validator::isFraction
*/

