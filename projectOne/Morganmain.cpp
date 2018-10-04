#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstring>
#include <cctype>
#include <vector>

// For readability
enum state { UNKNOWN, LETTER, DIGIT, OPERATOR, REAL, SEPARATOR };

// This class stores each lexeme and it's type
class Token
{
public: 
	Token(std::string lex, state type);
	void printToken();
private:
	std::string lexeme;
	state tokenType;
};

// Initializer
Token::Token(std::string lex, state type)
{
	lexeme = lex;
	tokenType = type;
}

// Prints the token. Just using cout for now for testing but this should be able to print to the file as well
void Token::printToken()
{
	std::cout << lexeme << " - " << tokenType;
}

// Our state machine. I believe the table is correct but I'm having trouble testing it. This is unfinished but hopefully the general idea is correct
class FSM
{
public:
	FSM();
	std::string createToken;
	void changeState(char newCharacter, state characterType);
  
private:
	int fsmStateTable[13][5];
	int currentState;
	int previousState;
	std::string currentLexeme;
	int currentLexemeType;
};

// Initializer
FSM::FSM()
{
	// Unknown, character, digit, operator, real
	int fsmStateTable[13][5] = { {0,0,0,0,0},
	{12,5,6,7,12},
	{12,5,12,12,12},
	{12,6,12,12,12},
	{12,12,7,12,12},
	{12,5,10,12,12},
	{12,12,6,12,8},
	{12,12,12,12,12},
	{12,12,9,12,12},
	{12,12,9,12,12},
	{12,11,10,12,12},
	{12,11,10,12,12},
	{12,12,12,12,12} };
	int currentState = 1;
	int previousState = 0;
	std::string currentLexeme = "";
	int currentLexemeType = 0;
}

// Uses the current state and the new character type to find the new state using the array table above.
void FSM::changeState(char newCharacter, state characterType)
{
	previousState = currentState; 
	currentState = fsmStateTable[previousState][int(characterType)];
	std::cout << "current state is " << currentState << std::endl;

	// This is unfinished. We need to add the character to the current lexeme if valid
	if (currentState != 12)
	{
		currentLexeme =+ newCharacter;
	}	
	else
	{
		std::cout << currentLexeme << std::endl;
		currentLexeme = "";
		currentLexemeType = 0;
	}
};


int main()
{
	FSM stateMachine;
	std::vector<Token*> tokenList;
	Token* currentToken;
	std::string lexeme;
	std::string line;
	char character;

	// This file is hard coded for testing purposes. We can have a prompt if you'd like
	std::ifstream inFile;
	inFile.open("C:\\Users\\Morgan\\source\\repos\\sourceTest1.txt");
	if (inFile.is_open())
	{
		std::cout << "File Opened Successfully.\n";
	}
	else {
		std::cout << "File not found.\n";
		return 0;
	}

	// This could be better, I'm just trying to test the state machine

	while (inFile.get(character))
	{
		// If the character is a separator, add the token to our list and avoid the FSM
		if (character == '(' || character == ')')
		{
			lexeme = character;
			currentToken = new Token(lexeme, SEPARATOR);
			tokenList.push_back(currentToken);
		}
		// If the character is a '.', send to state machine with state REAL (4)
		else if (character == '.')
		{
			stateMachine.changeState(character, REAL);
		}
		// If the character is an alphabet character, send to state machine with state LETTER (1)
		else if (isalpha(character))
		{
			stateMachine.changeState(character, LETTER);
		}
		// If the character is a digit, send to state machine with state DIGIT (2)
		else if (isdigit(character))
		{
			stateMachine.changeState(character, DIGIT);
		}
		// Operator else if will go here
	}

	inFile.close();
	return 0;

}
