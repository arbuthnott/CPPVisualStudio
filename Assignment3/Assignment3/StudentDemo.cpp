// Driver file for assignment 3

#include <conio.h>
#include <string>
#include "Validator.h"
#include "Student.h"
#include <iostream>
using namespace std;

void doDemo() {
	// initialize the validator
	Validator val;

	// Welcome message
	cout << "START STUDENT DEMO" << endl;
	cout << "***************************************" << endl << endl;

	// Prompt user for info to create two Students.
	cout << "We need to collect data to create two Students." << endl;
	cout << "We'll start with studentA." << endl;
	string nameA = val.getName("Name for studentA: ");
	Student studentA(nameA);

	cout << endl << "Now enter courses for studentA." << endl;
	cout << "Enter as many as you want," << endl;
	cout << "enter \"done\" when you are finished." << endl;
	cout << "-----------------------------------" << endl;
	string course = val.getCourse("Enter a course: ");
	while (course != "done") {
		studentA.addCourse(course);
		course = val.getCourse("Enter a course: ");
	}

	cout << endl << "studentA's data has been recorded:" << endl;
	cout << "\t" << studentA.toString() << endl << endl;

	// second student.
	cout << "Next we'll create studentB." << endl;
	string nameB = val.getName("Please enter a name for studentB: ");
	Student studentB(nameB);

	cout << endl << "Now enter courses for studentB." << endl;
	cout << "Enter as many as you want," << endl;
	cout << "enter \"done\" when you are finished." << endl;
	cout << "-----------------------------------" << endl;
	course = val.getCourse("Enter a course: ");
	while (course != "done") {
		studentB.addCourse(course);
		course = val.getCourse("Enter a course: ");
	}

	cout << endl << "studentB's data has been recorded:" << endl;
	cout << "\t" << studentB.toString() << endl << endl;

	cout << "Push any key for a demo of the copy constructor";
	_getch();

	cout << endl << endl << "***************************************" << endl << endl;

	// demo the copy constructor.
	cout << endl << "We'll now create a third student, studentC" << endl;
	cout << "using a copy constructor : Student studentC(studentA)" << endl;
	Student studentC(studentA);
	cout << "Verify the new student matches studentA." << endl;

	cout << "Resulting data for studentC:" << endl;
	cout << "\t" << studentC.toString() << endl << endl;

	studentA.addCourse("Anthropology");
	cout << "We'll add the class 'Anthropology' to studentA" << endl;
	cout << "Verify that the changes don't carry through to studentC." << endl;
	cout << "Result of studentA.addCourse('Anthropology'):" << endl;
	cout << "studentA:" << endl << "\t" << studentA.toString() << endl;
	cout << "studentC:" << endl << "\t" << studentC.toString() << endl << endl;

	studentC.addCourse("ScreenPrinting");
	cout << "We'll add the class 'ScreenPrinting' to studentC" << endl;
	cout << "Verify that the changes don't carry through to studentA." << endl;
	cout << "Result of studentC.addCourse('ScreenPrinting'):" << endl;
	cout << "studentA:" << endl << "\t" << studentA.toString() << endl;
	cout << "studentC:" << endl << "\t" << studentC.toString() << endl << endl;

	cout << "Push any key for an assignment operator demo";
	_getch();

	cout << endl << endl << "***************************************" << endl << endl;

	// demo the assignment operator override.
	cout << "We'll copy studentB's values into studentC" << endl;
	cout << "using the assignment operator: studentC = studentB" << endl;
	studentC = studentB;
	cout << "Verify results:" << endl;
	cout << "studentA:" << endl << "\t" << studentA.toString() << endl;
	cout << "studentB:" << endl << "\t" << studentB.toString() << endl;
	cout << "studentC:" << endl << "\t" << studentC.toString() << endl << endl;

	studentA.addCourse("Math1A");
	studentB.addCourse("Math2B");
	studentC.addCourse("Math3C");
	cout << "We'll add courses to each student" << endl;
	cout << "to verify they are seperate:" << endl;
	cout << "\tstudentA.addCourse('Math1A')" << endl;
	cout << "\tstudentB.addCourse('Math2B')" << endl;
	cout << "\tstudentC.addCourse('Math3C')" << endl << endl;

	cout << "Results:" << endl;
	cout << "studentA:" << endl << "\t" << studentA.toString() << endl;
	cout << "studentB:" << endl << "\t" << studentB.toString() << endl;
	cout << "studentC:" << endl << "\t" << studentC.toString() << endl << endl;

	cout << "Push any key to demo clearing the courses" << endl;
	cout << "and deletion as students go out of scope.";
	_getch();

	cout << endl << endl << "***************************************" << endl << endl;
	studentA.clearCourses();
	studentB.clearCourses();
	studentC.clearCourses();
	cout << "Clearing the courses of the students will" << endl;
	cout << "not destroy them, but will empty their" << endl;
	cout << "course lists to zero.  We use:" << endl;
	cout << "\tstudentA.clearCourses()" << endl;
	cout << "\tstudentB.clearCourses()" << endl;
	cout << "\tstudentC.clearCourses()" << endl;
	cout << "The result:" << endl;
	cout << "studentA:" << endl << "\t" << studentA.toString() << endl;
	cout << "studentB:" << endl << "\t" << studentB.toString() << endl;
	cout << "studentC:" << endl << "\t" << studentC.toString() << endl << endl;
}

int main() {

	doDemo();

	cout << endl << "Push any key to end the demo" << endl;
	cout << "and close the console.";

	_getch();
	return 0;
}