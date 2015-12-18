// Implementation file for class Validator

#include <conio.h>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include "Validator.h"
using namespace std;

// Constructor and Destructor
Validator::Validator() {}
Validator::~Validator() {}

// Generic input collector - gaurd against unwanted keystrokes
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

// collect a positive Integer
string Validator::getPositiveInteger(string message) {
	cout << message;
	string input;
	input = getInput();

	string intPattern = "^[0-9]+$";
	regex intReg(intPattern);

	while (!regex_search(input, intReg)) {
		cout << "Please enter a Positive Integer." << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}

// collect a positive integer in a certain range
int Validator::getIntInRange(int low, int high, string message) {
	int inputInt = stoi(getPositiveInteger(message));
	while (inputInt < low || inputInt > high) {
		cout << "Please enter an integer between " << low << " and " << high << endl << endl;
		inputInt = stoi(getPositiveInteger(message));
	}
	return inputInt;
}

// Collect one of y,n,Y,N.  Return as only y or n.
string Validator::getYN(string message) {
	cout << message;
	string input;
	input = getInput();
	string ynPattern = "^[ynYN]$";
	regex ynReg(ynPattern);
	while (!regex_search(input, ynReg)) {
		cout << "Please enter only 'y' or 'n'." << endl << endl;
		cout << message;
		input = getInput();
	}
	if (input == "y" || input == "Y") {
		return "y";
	}
	else {
		return "n";
	}
}