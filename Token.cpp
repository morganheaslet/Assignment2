#include "Token.h"

Token::Token()
{
	lexeme = "";
	tokenType = UNKNOWN;
}
Token::Token(std::string lex, state type)
{
	lexeme = lex;
	tokenType = type;
}

void Token::changeLexeme(std::string newLexeme)
{
	lexeme = newLexeme;
}

void Token::addLexeme(char newChar)
{
	lexeme = lexeme + newChar;
}

void Token::changeType(state newType)
{
	tokenType = newType;
}

std::string Token::getLexeme()
{
	return lexeme;
}

state Token::getType()
{
	return tokenType;
}

// Prints the token. Just using cout for now for testing but this should be able to print to the file as well
void Token::printToken()
{
	std::string tokenTypeString;
	switch (tokenType)
	{
	case 0:
		tokenTypeString = "UNKNOWN";
		break;
	case 1:
		tokenTypeString = "OPERATOR";
		break;
	case 2:
		tokenTypeString = "DIGIT";
		break;
	case 3:
		tokenTypeString = "OPERATOR";
		break;
	case 4:
		tokenTypeString = "REAL";
		break;
	case 5:
		tokenTypeString = "SEPARATOR";
		break;
	case 6:
		tokenTypeString = "KEYWORD";
		break;
	}
	std::cout << lexeme << "                      " << tokenTypeString << std::endl;
}
