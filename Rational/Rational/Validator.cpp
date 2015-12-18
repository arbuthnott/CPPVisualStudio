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
	cout << endl;
	return input;
}  // end method Validator::getInput

string Validator::getFraction(string message) {
	cout << message;
	string input;
	input = getInput();
	while (!isFraction(input)) {
		cout << "Please enter a fraction in form '#/#' where each # is any integer." << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}

string Validator::getExpression(string message) {
	cout << message;
	string input;
	input = getInput();
	while (opPos(input) == -1 && input != "demo") {
		cout << "Please enter a valid single-operation statement using '+', '-', '*' or '/'." << endl << endl;
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

bool Validator::isFraction(string input) {
	string fracPattern = "^\\s*-?\\s?\\d+\\s*$|^\\s*-?\\s?\\d+\\s*\\/\\s*-?\\s?\\d+\\s*$";
	regex fracReg(fracPattern);
	return regex_search(input, fracReg);
} // end method Validator::isFraction

/**
 * Used to check if a string represents an expression, and return the operation position.
 * Returns -1 if the string is not a valid expression.
 */
int Validator::opPos(string input) {
	string simpleOps = "+*";
	int pos = 0;
	for (int idx = 0; idx < simpleOps.size(); idx++) {
		char op = simpleOps[idx];
		pos = input.find(op);
		if (pos != string::npos) {
			string left = input.substr(0, pos);
			string right = input.substr(pos + 1, string::npos);
			if ((isFraction(left) && isFraction(right))) {
				return pos;
			}
			else {
				return -1;
			}
		}
	}

	// Check for a subtraction. Complicated because '-' can appear in fractions as well.
	pos = input.find('-');
	while (pos != string::npos) {
		string left = input.substr(0, pos);
		string right = input.substr(pos + 1, string::npos);
		if ((isFraction(left) && isFraction(right))) {
			return pos;
		}
		pos = input.find('-', pos + 1);
	}

	// now have to check for divisions.  Count the '/'s
	int numDivs = 0;
	pos = input.find("/");
	while (pos != string::npos) {
		numDivs++;
		pos = input.find("/", pos + 1);
	}
	if (numDivs == 1) {
		if (isFraction(input)) {
			return input.find('/');
		}
	}
	else if (numDivs == 2) {
		// for now, treat as frac / whole, ie 1/2/3 is interpreted (1/2)/3
		// get position of 2nd '/'
		pos = input.rfind("/");
		string left = input.substr(0, pos);
		string right = input.substr(pos + 1, string::npos);
		if (isFraction(left) && isFraction(right)) {
			return pos;
		}
	}
	else if (numDivs == 3) {
		// get position of 2nd '/'
		pos = input.find("/");
		pos = input.find("/", pos + 1);
		string left = input.substr(0, pos);
		string right = input.substr(pos + 1, string::npos);
		if (isFraction(left) && isFraction(right)) {
			return pos;
		}
	}
	return -1;
}