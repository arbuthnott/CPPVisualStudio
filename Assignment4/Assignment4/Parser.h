// header file for class Parser

#include <string>
using namespace std;

#ifndef PARSER_H
#define PARSER_H
class Parser
{
public:
	Parser();
	~Parser();
	static string parseCPPForWeb(string, string);
	static void translate(string*);
	static void replaceAll(string*, string, string);
	static void replaceOne(string*, int, int, string);
};

#endif

