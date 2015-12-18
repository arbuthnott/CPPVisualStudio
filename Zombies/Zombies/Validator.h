// Header file for class Validator
// class to collect and validate command line input.

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
	string getPositiveInteger(string);
	int getIntInRange(int, int, string);
	string getYN(string);
};

#endif