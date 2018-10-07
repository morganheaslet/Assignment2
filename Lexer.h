#include <string>
#include <iostream>
#include "Token.h"
#include "FSM.h"
#include "state.h"
#include <fstream>
class Lexer
{
public:
	Lexer();
	void getLine(std::string inputLine);
    void parseLine();
	Token returnToken();
	void clearToken();
private:
	FSM stateMachine;
	std::string line;
    std::string outputLine;
    Token token;
	bool complete;
};
