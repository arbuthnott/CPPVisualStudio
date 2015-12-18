// Header file for class Validator

#include <string>

#ifndef VALIDATOR_H
#define VALIDATOR_H
using namespace std;

class Validator {
private:

public:
	Validator();
	~Validator();
	string getInput();
	string getCPPFileName(string);
	string getHTMLFileName(string);
	string getYN(string);
};

#endif