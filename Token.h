#include <string>
#include <iostream>
#include "state.h"

class Token
{
public:
	Token();
	Token(std::string lex, state type);
	void changeLexeme(std::string newLexeme);
	void addLexeme(char newChar);
	void changeType(state newType);
	std::string getLexeme();
	state getType();
    void printToken();
private:
	std::string lexeme;
	state tokenType;
};
