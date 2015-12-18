// Implementation file for class Parser

#include <string>
#include <fstream>
#include <iostream>
#include "Parser.h"
#include "Validator.h"
using namespace std;

// constructor and destructor
Parser::Parser() {}
Parser::~Parser() {}

// Return "" on success, return a specific error message on failure.
string Parser::parseCPPForWeb(string infileName, string outfileName) {
	try {
		ifstream inStream("H:\\" + infileName);
		if (inStream.fail()) {
			// failed input open
			throw "Couldn't open input file.  Please make sure H:\\" + infileName + " exists.";
		}
		
		ofstream outStream("H:\\" + outfileName);
		if (outStream.fail()) {
			// failed output open
			inStream.close();
			throw "Couldn't access or create H:\\" + outfileName + " for output.";
		}

		outStream << "<PRE>" << endl;
		string line;
		while (!inStream.eof()) {
			getline(inStream, line); // read from inStream to line
			if (inStream.fail()) {
				// failed to read in
				inStream.close();
				outStream.close();
				throw "Couldn't read a line.";
			}
			
			translate(&line);
			outStream << line << endl;
			if (outStream.fail()) {
				// failed to write out
				inStream.close();
				outStream.close();
				throw "Couldn't write a line.";
			}
		}
		outStream << "</PRE>" << endl;
		inStream.close();
		outStream.close();
	}
	catch (string manual_error) {
		return manual_error;
	}
	catch (ios_base::failure fail) {
		return "Error during file input/output";
	}
	return "";
}

// translates a single line. No return - changes in place
void Parser::translate(string* htmString) {
	replaceAll(htmString, "<", "&lt;");
	replaceAll(htmString, ">", "&gt;");
}

// do a string replace.  No return - changes in place.
void Parser::replaceAll(string* subject, string oldstr, string newstr) {
	if (newstr.find(oldstr) == string::npos) { // this gaurds agains infinite looping.
		int pos = (*subject).find(oldstr);
		while (pos != string::npos) {
			replaceOne(subject, pos, pos + oldstr.size(), newstr);
			pos = (*subject).find(oldstr);
		}
	}
}

void Parser::replaceOne(string* subject, int startPos, int endPos, string newstr) {
	(*subject) = subject->substr(0, startPos) + newstr + subject->substr(endPos, string::npos);
}
