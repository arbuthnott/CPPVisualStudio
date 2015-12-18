// Implementation of Fraction class

#include <iostream>
#include <conio.h>
#include <math.h>
#include <string>
#include "Fraction.h"
#include "Validator.h"
using namespace std;

// Constructors and Destructor
Fraction::Fraction() {
	this->num = 0;
	this->denom = 1;
}
Fraction::Fraction(int top) {
	this->num = top;
	this->denom = 1;
}
Fraction::Fraction(int top, int bottom) {
	if (bottom == 0) {
		this->num = 0;
		this->denom = 0;
	}
	else {
		this->num = top;
		this->denom = bottom;
		reduce();
	}
}
Fraction::Fraction(string input) {
	string nm, dnm;
	int divPos = input.find('/');
	if (divPos == string::npos) {
		this->num = stoi(input);
		this->denom = 1;
	}
	else {
		this->num = stoi(input.substr(0,divPos));
		this->denom = stoi(input.substr(divPos + 1, string::npos));
		if (this->denom == 0) {
			this->num = 0;
			this->denom = 0;
		}
		else {
			reduce();
		}
	}
}
Fraction::~Fraction() {}

// The reduce method - put fraction in lowest terms, make denom positive,
// and make sure zero is represented by 0/1.
void Fraction::reduce() {
	int lower, higher;
	// look for greatest common divisor, starting from the lower
	// of num and denom.
	if (this->num <= this->denom) {
		lower = num;
		higher = denom;
	}
	else {
		lower = denom;
		higher = num;
	}
	if (this->denom == 0) { // cannot reduce
		return;
	}
	else if (lower < 0) { // for our for-loop
		lower *= -1;
	}
	for (int idx = lower; idx > 1; idx--) {
		if (lower % idx == 0) {
			if (higher % idx == 0) {
				this->num /= idx;
				this->denom /= idx;
				break; // only divide by greatest!
			}
		}
	}
	// make sure denom is positive.
	if (this->denom < 0) {
		denom *= -1;
		num *= -1;
	}
	// if num is 0 set denom to 1
	if (this->num == 0) {
		this->denom = 1;
	}
}

string Fraction::toString() {
	if (this->denom == 1) {
		return to_string(this->num);
	}
	else if (this->denom == 0) {
		return "BAD FRACTION";
	}
	else {
		return to_string(this->num) + "/" + to_string(this->denom);
	}
}

// Arithmetic operations +,-,*,/
Fraction Fraction::operator+(Fraction otherFrac) {
	int newNum = this->num * otherFrac.denom + this->denom * otherFrac.num;
	int newDenom = this->denom * otherFrac.denom;
	if (newDenom == 0) { newNum = 0; }
	Fraction sum(newNum, newDenom);
	sum.reduce();
	return sum;
}

Fraction Fraction::operator-(Fraction otherFrac) {
	int newNum = this->num * otherFrac.denom - this->denom * otherFrac.num;
	int newDenom = this->denom * otherFrac.denom;
	if (newDenom == 0) { newNum = 0; }
	Fraction dif(newNum, newDenom);
	dif.reduce();
	return dif;
}

Fraction Fraction::operator*(Fraction otherFrac) {
	int newNum = this->num * otherFrac.num;
	int newDenom = this->denom * otherFrac.denom;
	if (newDenom == 0) { newNum = 0; }
	Fraction prod(newNum, newDenom);
	prod.reduce();
	return prod;
}

Fraction Fraction::operator/(Fraction otherFrac) {
	int newNum = this->num * otherFrac.denom;
	int newDenom = this->denom * otherFrac.num;
	if (newDenom == 0) { newNum = 0; }
	Fraction quot(newNum, newDenom);
	quot.reduce();
	return quot;
}

// boolean operations ==, <, >, <=, >=
bool Fraction::operator==(Fraction otherFrac) {
	int left = this->num * otherFrac.denom;
	int right = this->denom * otherFrac.num;
	return left == right;
}

bool Fraction::operator<(Fraction otherFrac) {
	int left = this->num * otherFrac.denom;
	int right = this->denom * otherFrac.num;
	return left < right;
}

bool Fraction::operator>(Fraction otherFrac) {
	int left = this->num * otherFrac.denom;
	int right = this->denom * otherFrac.num;
	return left > right;
}

bool Fraction::operator<=(Fraction otherFrac) {
	int left = this->num * otherFrac.denom;
	int right = this->denom * otherFrac.num;
	return left <= right;
}

bool Fraction::operator>=(Fraction otherFrac) {
	int left = this->num * otherFrac.denom;
	int right = this->denom * otherFrac.num;
	return left >= right;
}

ostream& operator<<(ostream& os, Fraction frac) {
	os << frac.toString();
	return os;
}

istream& operator>>(istream& is, Fraction& frac) {
	Validator val;
	string input;
	getline(is, input);
	if (!val.isFraction(input)) {
		is.setstate(istream::failbit);
	}
	else {
		int divPos = input.find('/');
		if (divPos == string::npos) {
			frac.num = stoi(input);
			frac.denom = 1;
		}
		else {
			frac.num = stoi(input.substr(0, divPos));
			frac.denom = stoi(input.substr(divPos + 1, string::npos));
			if (frac.denom == 0) {
				frac.denom = 1;
			}
			frac.reduce();
		}
	}
	return is;
}