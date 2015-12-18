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

// collect a valid windows .cpp file name or path
string Validator::getCPPFileName(string message) {
	cout << message;
	string input;
	input = getInput();

	string dirPattern = "[^<\\\\>\\|/:\\.\"\\?\\*]*[^<\\\\>\\|/:\\.\"\\?\\*\\s]\\\\";
	string filePattern = "\\.?[^<\\\\>\\|:/\\.\"\\?\\*]*[^<\\\\>\\|/:\\.\"\\?\\*\\s]\\.cpp";
	string pathPattern = "^(" + dirPattern + ")*" + filePattern + "$";

	string resPattern = "^(([cC][oO][nN])|([pP][rR][nN])|([aA][uU][xX])|([nN][uU][lL])|([cC][oO][mM][1-9])|([lL][pP][tT][1-9]))\\.cpp$";
	regex reservedReg(resPattern);

	regex fileReg(pathPattern);
	while (!regex_search(input, fileReg) || regex_search(input, reservedReg)) {
		cout << "Invalid windows cpp file path. Note, names can't include <  >  :  \" / \\ | ? or *" << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
}

// collect a valit .htm or .html file name or path
string Validator::getHTMLFileName(string message) {
	cout << message;
	string input;
	input = getInput();

	string dirPattern = "[^<\\\\>\\|/:\\.\"\\?\\*]*[^<\\\\>\\|/:\\.\"\\?\\*\\s]\\\\";
	string filePattern = "\\.?[^<\\\\>\\|/:\\.\"\\?\\*]*[^<\\\\>\\|/:\\.\"\\?\\*\\s]\\.html?";
	string pathPattern = "^(" + dirPattern + ")*" + filePattern + "$";

	string resPattern = "^(([cC][oO][nN])|([pP][rR][nN])|([aA][uU][xX])|([nN][uU][lL])|([cC][oO][mM][1-9])|([lL][pP][tT][1-9]))\\.html?$";
	regex reservedReg(resPattern);

	regex fileReg(pathPattern);
	while (!regex_search(input, fileReg) || regex_search(input, reservedReg)) {
		cout << "Invalid windows html file path. Note, names can't include <  >  :  \" / \\ | ? or *" << endl << endl;
		cout << message;
		input = getInput();
	}
	return input;
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

