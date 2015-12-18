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
	string getFraction(string);
	string getExpression(string);
	string getYN(string);
	bool isFraction(string);
	int opPos(string);
};

#endif