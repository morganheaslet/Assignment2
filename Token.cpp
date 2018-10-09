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

// Converts the token type to it's string version and outputs the token type and lexeme to an output file (file name received as argument)
void Token::printToken(std::string output)
{
	std::ofstream outputFile;
	outputFile.open(output, std::ios_base::app);
	std::string tokenTypeString;
	switch (tokenType)
	{
	case 0:
		tokenTypeString = "UNKNOWN";
		break;
	case 1:
		tokenTypeString = "IDENTIFIER";
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
    
	outputFile << std::setw(20) << std::left << lexeme << " - " << tokenTypeString << std::endl;
	outputFile.close();
}
