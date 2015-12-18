// Demo of the Fraction class
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <time.h>
#include "Fraction.h"
#include "Validator.h"
#include "Utility.h"
using namespace std;



int main() {
	// Welcome message
	std::cout << "Starting your fraction calculator!" << endl;
	std::cout << "**********************************" << endl << endl;
	std::cout << "You can enter single operations using +, -, *, or /." << endl;
	std::cout << "Ex:" << endl;
	std::cout << "\t5/7 - -2/3" << endl;
	std::cout << "\t-1/2 + 6" << endl;
	std::cout << "You can also enter 'demo', then be shown a quick demo of operations on randomly generated fractions" << endl;
	std::cout << endl << "Let's begin!" << endl;

	// initialize
	Validator val;
	Utility util;
	string keepGoing = "y";
	string bools[] = { "False", "True" };

	while (keepGoing == "y") {
		string input = val.getExpression("Enter an expression to solve: ");
		if (input == "demo") {
			// code for the demo
			// create some random fractions
			srand(time(0));
			int num1 = rand() % 21 - 10;
			int num2 = rand() % 21 - 10;
			int denom1 = rand() % 10 + 1;
			int denom2 = rand() % 10 + 1;
			Fraction frac1(num1, denom1);
			Fraction frac2(num2, denom2);
			std::cout << endl << "For the demo, using random fractions:" << endl;
			std::cout << frac1 << ", and " << frac2 << endl << endl;

			// display the outputs.
			std::cout << frac1 << " + " << frac2 << " = " << frac1 + frac2 << endl;
			std::cout << frac1 << " - " << frac2 << " = " << frac1 - frac2 << endl;
			std::cout << frac1 << " * " << frac2 << " = " << frac1 * frac2 << endl;
			std::cout << frac1 << " / " << frac2 << " = " << frac1 / frac2 << endl;
			std::cout << frac1 << " == " << frac2 << ": " << bools[frac1 == frac2] << endl;
			std::cout << frac1 << " < " << frac2 << ": " << bools[frac1 < frac2] << endl;
			std::cout << frac1 << " <= " << frac2 << ": " << bools[frac1 <= frac2] << endl;
			std::cout << frac1 << " > " << frac2 << ": " << bools[frac1 > frac2] << endl;
			std::cout << frac1 << " >= " << frac2 << ": " << bools[frac1 >= frac2] << endl;
		}
		else {
			int operPos = val.opPos(input);
			char op = input[operPos];
			Fraction left(input.substr(0, operPos));
			Fraction right(input.substr(operPos + 1, string::npos));
			Fraction result;
			// do switch case on op to generate result
			switch (op) {
			case '+':
				result = left + right;
				break;
			case '-':
				result = left - right;
				break;
			case '*':
				result = left * right;
				break;
			case '/':
				result = left / right;
				break;
			}

			// spit out the answer.
			std::cout << left << " " << op << " " << right << " = " << result << endl << endl;
		}

		keepGoing = val.getYN("Enter another expression? (y/n) ");
	}
	// exit message
	std::cout << endl << endl << "Thanks for using the calculator." << endl;
	std::cout << "Push any key to exit." << endl;
	_getch();
}