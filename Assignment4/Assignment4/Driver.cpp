// Driver for Assignment 4: CPP to HTML conversion

#include <string>
#include <conio.h>
#include <iostream>
#include "Validator.h"
#include "Parser.h"
using namespace std;

int main() {

	/*Validator val;
	string cppPath = "";
	while (cppPath != "done.cpp") {
		cppPath = val.getCPPFileName("Enter a cpp path: ");
		cout << cppPath << " is a good name" << endl << endl;
	}*/

	// Welcome message.  Give some file and dir guidelines.
	cout << "Welcome to the CPP -> HTML file converter." << endl << endl;
	cout << "**********************************************************************" << endl;
	cout << "* NOTES ON FILE INPUTS:" << endl << "*" << endl;
	cout << "* File Extensions are separated by a '.' (ex blah.cpp)" << endl;
	cout << "* Directories and files separated by a '\\' (ex path\\to\\file.html)" << endl;
	cout << "* The H drive is home, so 'myinput.cpp' is read from 'H:\\myinput.cpp'" << endl;
	cout << "* and 'path\\to\\file.html' refers to 'H:\\path\\to\\file.html'." << endl;
	cout << "**********************************************************************" << endl << endl;
	
	// initialize some variables.
	Validator val;
	string anotherRound = "y";
	string cppFile, htmFile, error;

	// start conversion loop
	while (anotherRound != "n") {
		cppFile = val.getCPPFileName("Enter an existing cpp file (Ex Driver.cpp): ");
		htmFile = val.getHTMLFileName("Enter a target html filename (Ex forWeb.html): ");

		try {
			error = Parser::parseCPPForWeb(cppFile, htmFile);
		}
		catch (...) { // catch all uncaught errors
			cout << "Caught an unknown exception! Closing the converter..." << endl;
			break; // exit the loop.
		}
		if (error == "") { // success
			cout << "Your file has been converted and stored in H:\\" << htmFile << endl;
		}
		else { // report error message for handled errors
			cout << "Encountered an error: " << error << endl;
		}
		cout << endl;
		anotherRound = val.getYN("Convert another file? (y/n) ");
	}

	// end message
	cout << endl << "Thanks for using file converter." << endl;
	cout << "Push any key to exit.";

	_getch();
	return 0;
}