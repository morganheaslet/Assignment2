#include "Lexer.h"
#include <iostream>
#include <fstream>

Lexer::Lexer()
{
}

void Lexer::getLine(std::string inputLine)
{
	line = inputLine;
	complete = false;
}

void Lexer::parseLine()
{
    
	char character;
	
	for (unsigned int i = 0; i < line.length(); i++)
	{
		character = line.at(i);

		if (character == '<' || character == '>' || character == '+')           // THE REST OF THE OPERATORS NEED TO BE FILLED IN HERE
		{
			stateMachine.changeState(OPERATOR);
			token.addLexeme(character);
		}
		else if (isdigit(character))
		{
			stateMachine.changeState(DIGIT);
			token.addLexeme(character);
		}
		else if (character == '.')
		{			
			stateMachine.changeState(REAL);
			token.addLexeme(character);
		}
		else if (isalpha(character))
		{
			stateMachine.changeState(LETTER);
			token.addLexeme(character);
		}
		else if (character == '(' || character == ')' || character == ' ')
		{
			// Prints a indentifier token and resets the state machine and token object
			if (stateMachine.getCurrentState() == 5 || stateMachine.getCurrentState() == 11)
			{
				token.changeType(LETTER);
				if (token.getLexeme() == "while")
				{
					token.changeType(KEYWORD);
				}
				token.printToken(); // TESTING
				clearToken();
				stateMachine.resetState();
			}
			// Prints an integer token and resets the state machine and token object
			else if (stateMachine.getCurrentState() == 6)
			{
				token.changeType(DIGIT);
				token.printToken(); // TESTING
				clearToken();
				stateMachine.resetState();
			}
			// Prints a real token and resets the state machine and token object
			else if (stateMachine.getCurrentState() == 9)
			{
				token.changeType(REAL);
				token.printToken(); // TESTING
				clearToken();
				stateMachine.resetState();
			}
			// Prints an operator token and resets the state machine and token object
			else if (stateMachine.getCurrentState() == 7 || stateMachine.getCurrentState() == 13)
			{
				token.changeType(OPERATOR);
				token.printToken();
				clearToken();
				stateMachine.resetState();
			}
			// Invalid token. Resets state machine and clears the token object
			else
			{
				clearToken();
				stateMachine.resetState();
			}
			if (character == '(' || character == ')')
			{
				token.addLexeme(character);
				token.changeType(SEPARATOR);
				token.printToken();
				clearToken();
			}
		}
	}

	// The below code checks if last word in line was valid

	// Prints a indentifier token and resets the state machine and token object
	if (stateMachine.getCurrentState() == 5 || stateMachine.getCurrentState() == 11)
	{
		token.changeType(LETTER);
		token.printToken(); // TESTING
		clearToken();
		stateMachine.resetState();
	}
	// Prints an integer token and resets the state machine and token object
	else if (stateMachine.getCurrentState() == 6)
	{
		token.changeType(DIGIT);
		token.printToken(); // TESTING
		clearToken();
		stateMachine.resetState();
	}
	// Prints a real token and resets the state machine and token object
	else if (stateMachine.getCurrentState() == 9)
	{
		token.changeType(REAL);
		token.printToken(); // TESTING
		clearToken();
		stateMachine.resetState();
	}
	// Invalid token. Resets state machine and clears the token object
	else
	{
		clearToken();
		stateMachine.resetState();
	}
}
Token Lexer::returnToken()
{
	return token;
}

void Lexer::clearToken()
{
	token.changeLexeme("");
	token.changeType(UNKNOWN);
}

