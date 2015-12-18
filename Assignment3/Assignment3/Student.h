// Header file for class Student

#include <string>

#ifndef STUDENT_H
#define STUDENT_H
using namespace std;

class Student
{
private:
	string name;
	int numCourses;
	string* courseList;
public:
	// constructors/destructor
	Student();
	Student(string); // name only.
	~Student();
	
	// copy Constructor
	Student(const Student&);
	
	// copy Assignment Operator Override
	Student& operator=(const Student);
	
	// getters and setters
	string getName();
	int getNumCourses();
	string* getCourseList();
	void setName(string);
	void setCourseList(int, const string*);
	
	// misc
	void addCourse(string);
	void clearCourses();
	string toString();
	friend ostream& operator<<(ostream&, Student);
	friend istream& operator>>(istream&, Student&);
};

#endif