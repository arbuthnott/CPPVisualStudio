// Implementation of the Utility class

#include <string>
#include <vector>
#include "Utility.h"
using namespace std;

// Constructor and Destructor
Utility::Utility() {}
Utility::~Utility() {}

vector<string> Utility::split(string content, string delim) {
	vector<string> vec;
	int startAt = 0;
	int nextDelim = content.find(delim);
	while (nextDelim != string::npos) {
		vec.push_back(content.substr(startAt, nextDelim - startAt));
		startAt = nextDelim + delim.size();
		nextDelim = content.find(delim, startAt);
	}
	vec.push_back(content.substr(startAt, content.length()));
	return vec;
}