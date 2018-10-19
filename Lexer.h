#include <string>
#include <iostream>
#include <fstream>
#include "Token.h"
#include "FSM.h"
#include "state.h"

class Lexer
{
public:
	Lexer();
	Lexer(std::string outFile);
	void getLine(std::string inputLine);
    Token getToken();
	void clearToken();
	bool lineEmpty();

private:
	FSM stateMachine; // State Machine
	std::string line; // Current line to be parsed
	std::string outputFile; // Name of output file
    Token token;  // Token object to store lexemes
	bool invalid; // True if within comment brackets
	bool emptyLine;
};
