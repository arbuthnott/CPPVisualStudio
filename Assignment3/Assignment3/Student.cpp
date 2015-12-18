// implementation file for Student class.

#include "Student.h"
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

// constructors/destructor
Student::Student() {
	if ((rand() % 2) < 1) {
		this->name = "John Doe";
	}
	else {
		this->name = "Jane Doe";
	}
	this->numCourses = 0;
	this->courseList = 0; // the null pointer??
}
Student::Student(string inputname) {
	this->name = inputname;
	this->numCourses = 0;
	this->courseList = 0; // the null pointer.
}
Student::~Student() {
	if (this->courseList != 0) {
		delete[] this->courseList; // deletes the contents of memory
		this->courseList = 0; // safe the pointer - make it point to 0.
	}
	// output.
	cout << this->name << "'s DESTRUCTOR WAS CALLED" << endl;
}

// copy Constructor
Student::Student(const Student& otherStudent) {
	// copy name and numCourses the usual way.
	this->name = otherStudent.name;
	this->numCourses = otherStudent.numCourses;
	// must "Deep Copy" the course list.
	// Careful!  only if passed in Student courseList is pointing to something.
	if (otherStudent.courseList) {
		this->courseList = new string[this->numCourses]; // reserve space for course list.
		// now copy the contents.
		for (int idx = 0; idx < this->numCourses; idx++) {
			this->courseList[idx] = otherStudent.courseList[idx];
		}
	}
	else {
		// in this case, no stuff to deep copy
		this->courseList = 0;
	}
	// output.
	cout << "COPY CONSTRUCTOR USED TO CREATE STUDENT " << this->name << endl;
}

// copy Assignment Operator Override
Student& Student::operator=(const Student otherStudent) {
	// NEED:
	// -self assignment test
	// -support for chaining (so, return a value)
	// -deallocate old values of this object.
	if (this == &otherStudent) { // protection against self assignment
		return *this;
	}

	// now delete old content.
	delete[] this->courseList;

	// copy the content.
	string oldname = this->name;
	this->name = otherStudent.name;
	this->numCourses = otherStudent.numCourses;
	this->courseList = new string[this->numCourses];
	// contents of courseList item by item.
	for (int idx = 0; idx < this->numCourses; idx++) {
		this->courseList[idx] = otherStudent.courseList[idx];
	}

	// output and return value for chaining
	cout << "CALL TO " << oldname << "'s COPY ASSIGNMENT OPERATOR" << endl;
	return *this;
}

// getters and setters
string Student::getName() {
	return this->name;
}
int Student::getNumCourses() {
	return this->numCourses;
}
string* Student::getCourseList() {
	return this->courseList;
}
void Student::setName(string newName) {
	this->name = newName;
}
// This setter *copies* the contents of the new passed in list.
void Student::setCourseList(int newListSize, const string* newList) {
	// delete old courseList.
	if (this->numCourses != 0) {
		delete[] this->courseList;
	}
	this->numCourses = newListSize;
	// assign the new content.
	if (newList == 0) {
		this->courseList = 0;
	}
	else {
		for (int idx = 0; idx < this->numCourses; idx++) {
			this->courseList[idx] = newList[idx];
		}
	}
}

// misc
void Student::addCourse(string newCourse) {
	// create the new array.
	string* newCourseList = new string[this->numCourses + 1];
	for (int idx = 0; idx < this->numCourses; idx++) {
		newCourseList[idx] = this->courseList[idx];
	}
	newCourseList[this->numCourses] = newCourse;
	// newCourseList is complete.  Delete the old.
	if (this->numCourses != 0) {
		delete[] this->courseList;
	}
	// set to new values.
	this->numCourses++;
	this->courseList = newCourseList;
}
void Student::clearCourses() {
	if (this->courseList != 0) {
		delete[] this->courseList;
		this->numCourses = 0;
		this->courseList = 0;
	}
}
string Student::toString() {
	
	string output = this->name + " has " + to_string(this->numCourses) + " courses: ";
	if (this->numCourses == 0) {
		output += "no courses found!";
	}
	else {
		for (int idx = 0; idx < this->numCourses; idx++) {
			output += this->courseList[idx];
			if (idx < this->numCourses - 1) {
				output += ", ";
			}
		}
	}
	return output;
}

// input output operator overloads (as friend functions)
ostream& operator<<(ostream& os, Student otherStudent) {
	os << otherStudent.toString();
	return os;
}

istream& operator>>(istream& is, Student& otherStudent) {
	string input;
	getline(is, input);
	otherStudent.name = input;
	otherStudent.numCourses = 0;
	otherStudent.courseList = 0;
	return is;
}
