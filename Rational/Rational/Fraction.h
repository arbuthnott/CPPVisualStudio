// Header file for class Fraction

#ifndef FRACTION_H
#define FRACTION_H
using namespace std;

class Fraction {
private:
	int num;
	int denom;
public:
	Fraction(void); // constructor
	Fraction(int); // num only constructor
	Fraction(int, int); // num and denom constructor
	Fraction(string); // string constructor
	virtual ~Fraction(void); // destructor

	void reduce(); // reduce yourself
	string toString();
	Fraction operator+(Fraction);
	Fraction operator-(Fraction);
	Fraction operator*(Fraction);
	Fraction operator/(Fraction);
	bool operator==(Fraction);
	bool operator>(Fraction);
	bool operator<(Fraction);
	bool operator<=(Fraction);
	bool operator>=(Fraction);
	friend ostream& operator<<(ostream&, Fraction);
	friend istream& operator>>(istream&, Fraction&);
};

#endif