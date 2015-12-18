// Driver for the simulation

#include <conio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "City.h"
#include "Validator.h"
using namespace std;

// method to pause
void wait(int millis) {
	this_thread::sleep_for(chrono::milliseconds(millis));
}

// method to get a short report on the city.
string getReport(City* city, int iters) {
	string output = "Report after " + std::to_string(iters) + " iterations:\n";
	int numZombies = city->getZombies().size();
	int numHumans = city->getHumans().size();
	output += "Zombies: " + to_string(numZombies) + "\n";
	output += "Humans: " + to_string(numHumans) + "\n";
	return output;
}

int main() {

	// create some objects
	City* city;
	Validator val;

	// vars to use during game loop
	string useDefault, shouldWait;
	int numHumans, numZombies, numIters;
	bool waitForIter;

	string anotherRound = "y";

	// Welcome and collect simulation settings.
	cout << "Welcome to the Zombie Apocalypse Simulator!" << endl;

	// start loop
	while (anotherRound == "y") {
		city = new City; // new city object
		cout << "The default simulation starts with 100 humans, 5 zombies, and cycles on a timer to a maximum of 100 iterations." << endl << endl;
		useDefault = val.getYN("Would you like to use the default settings? (y/n) ");

		// set default settings
		numHumans = 100;
		numZombies = 5;
		numIters = 100;
		waitForIter = false;
		if (useDefault == "n") { // replace default settings
			numHumans = val.getIntInRange(1, (GRID_HEIGHT - 1)*(GRID_WIDTH - 1), "Enter the number of humans: ");
			numZombies = val.getIntInRange(1, (GRID_HEIGHT - 1)*(GRID_WIDTH - 1), "Enter the number of zombies: ");
			numIters = val.getIntInRange(5, 500, "Enter the maximum number of iterations: ");
			shouldWait = val.getYN("Would you like iteration to wait for you to push any key? (y/n) ");
			waitForIter = shouldWait == "y";
		}

		// setup the simulation.
		for (int idx = 0; idx < numHumans; idx++) {
			city->addRandomHuman();
		}
		for (int idx = 0; idx < numZombies; idx++) {
			city->addRandomZombie();
		}
		string report;
		int iterations = 0;

		// start the simulation
		while (iterations <= numIters && city->stillAlive()) {
			system("cls");
			report = getReport(city, iterations);
			cout << *city << report << endl;
			iterations++;
			city->iterate();
			if (waitForIter) { // pause for the user
				cout << "\tPUSH ANY KEY TO CONTINUE";
				_getch();
			}
			else { // short timer pause
				wait(100);
			}
		}

		cout << endl << "Simulation ended.";
		if (!city->stillAlive()) {
			cout << " EXTINCTION EVENT!" << endl;
		}
		delete city;
		city = 0;
		anotherRound = val.getYN(" Run another simulation? (y/n) ");
	}

	// exit the program
	cout << "Thanks for using the simulation!" << endl << "Push any key to exit.";
	_getch();
	return 0;
}