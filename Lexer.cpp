#include "Lexer.h"

Lexer::Lexer()
{}

// Constructor (receives name of output file and creates the header)
Lexer::Lexer(std::string outputFileName)
{
	outputFile = outputFileName;
	invalid = false;
	emptyLine = true;
	lineNum = 0;

	std::ofstream oFile;
	oFile.open(outputFile);
	oFile << std::setw(23) << std::left << "Lexeme" << "Token" << std::endl;
	oFile.close();
}

// Receives a string and stores it to be parsed
void Lexer::getLine(std::string inputLine)
{
	line = inputLine;
	emptyLine = false;
	lineNum++;
}

Token Lexer::getToken()
{
	char character;
	// Takes each character is checks its type, sends the type to the FSM, and adds the character to the Lexeme string. Once broken up by a separater
	// or whitespace, it checks the FSM to see if it's in a valid state. If it is, it prints the lexeme as a valid token. If not, it erases the lexeme
	// and continues where it left off
	for (unsigned int i = 0; i < line.length(); i++)
	{
		character = line.at(i);
		// Checks to see if the current character is between comment brackets
		if (character == '[' && line.at(i + 1) == '*')
		{
			invalid = true;
			i++;
		}

		if (invalid == true)
		{
			// Checks to see if character is the ending comment bracket
			if (character == '*' && line.at(i + 1) == ']')
			{
				invalid = false;
				i++;
			}
		}
		// Checks if character is between comment brackets, and ignores character is so
		else if (invalid == false)
		{
			// Checks if character is an operator
			if (character == '<' || character == '>' || character == '+' || character == '-' || character == '='
				|| character == '/' || character == '*' || character == '^' || character == '$')
			{
				stateMachine.changeState(OPERATOR);
				token.addLexeme(character);
			}
			// Checks if character is a digit
			else if (isdigit(character))
			{
				stateMachine.changeState(DIGIT);
				token.addLexeme(character);
			}
			// Checks if character is a period
			else if (character == '.')
			{
				stateMachine.changeState(REAL);
				token.addLexeme(character);
			}
			// Checks if character is an alphabet character
			else if (isalpha(character))
			{
				stateMachine.changeState(LETTER);
				token.addLexeme(character);
			}
			// Checks if character is a separator or white space and stops adding to the lexeme if so
			else if (character == '(' || character == ')' || character == ' ' || character == '{' || character == '}' || character == ';' 
				|| character == ':')
			{
				// Prints a indentifier token and resets the state machine and token object if current state is valid for identifier
				if (stateMachine.getCurrentState() == 5 || stateMachine.getCurrentState() == 11)
				{
					// Checks if identifer is a keyword, if so, changes the token type to "keyword"
					if (token.getLexeme() == "while" || token.getLexeme() == "and" || token.getLexeme() == "for" || token.getLexeme() == "if"
						|| token.getLexeme() == "whileend" || token.getLexeme() == "get" || token.getLexeme() == "return" || token.getLexeme() == "else"
						|| token.getLexeme() == "put" || token.getLexeme() == "int" || token.getLexeme() == "and" || token.getLexeme() == "or"
						|| token.getLexeme() == "compound" || token.getLexeme() == "assign" || token.getLexeme() == "return" || token.getLexeme() == "scan"
						|| token.getLexeme() == "print" || token.getLexeme() == "function")
					{
						token.changeType(KEYWORD);
					}
					// If the identifer is not a keyword, changes the token type to "Identifier"
					else
					{
						token.changeType(LETTER);
					}

					line = line.substr(i);
					stateMachine.resetState();
					token.changeLineNum(lineNum);
					return token;
				}
				// Prints an integer token and resets the state machine and token object if the current state is valid for integer
				else if (stateMachine.getCurrentState() == 6)
				{
					token.changeType(DIGIT);
					line = line.substr(i);
					stateMachine.resetState();
					token.changeLineNum(lineNum);
					return token;
				}
				// Prints a real token and resets the state machine and token object if the current state is valid for real
				else if (stateMachine.getCurrentState() == 9)
				{
					token.changeType(REAL);
					line = line.substr(i);
					stateMachine.resetState();
					token.changeLineNum(lineNum);
					return token;
				}
				// Prints an operator token and resets the state machine and token object if the current state is valid for operator
				else if (stateMachine.getCurrentState() == 7 || stateMachine.getCurrentState() == 13)
				{
					token.changeType(OPERATOR);
					line = line.substr(i);
					stateMachine.resetState();
					token.changeLineNum(lineNum);
					return token;
				}
				// Checks to see if the character is a valid separator (not whitespace)
				else if (character == '(' || character == ')' || character == ',' || character == '{' || character == '}'
					|| character == ';' || character == ':')
				{
					token.addLexeme(character);
					token.changeType(SEPARATOR);
					line = line.substr(i+1);
					stateMachine.resetState();
					token.changeLineNum(lineNum);
					return token;
				}
				// Invalid token if current state is not valid. Resets state machine and clears the token object
				else
				{
					line = line.substr(i+1);
					stateMachine.resetState();
					token.changeType(UNKNOWN);
					token.changeLineNum(lineNum);
					return token;
				}
			}
		}
	}

	emptyLine = true;
	line = "";
	// The below code checks if the last word in the line is valid (after the last character has been received)

	// Prints a indentifier token and resets the state machine and token object
	if (stateMachine.getCurrentState() == 5 || stateMachine.getCurrentState() == 11)
	{
		// Checks if identifer is a keyword, if so, changes the token type to "keyword"
		if (token.getLexeme() == "while" || token.getLexeme() == "and" || token.getLexeme() == "for" || token.getLexeme() == "if"
			|| token.getLexeme() == "whileend" || token.getLexeme() == "get" || token.getLexeme() == "return" || token.getLexeme() == "else"
			|| token.getLexeme() == "put" || token.getLexeme() == "int" || token.getLexeme() == "and" || token.getLexeme() == "or"
			|| token.getLexeme() == "compound" || token.getLexeme() == "assign" || token.getLexeme() == "return" || token.getLexeme() == "scan"
			|| token.getLexeme() == "print" || token.getLexeme() == "function")
		{
			token.changeType(KEYWORD);
		}
		// If the identifer is not a keyword, changes the token type to "Identifier"
		else
		{
			token.changeType(LETTER);
		}
				
		stateMachine.resetState();
		token.changeLineNum(lineNum);
		return token;
	}
	// Prints an integer token and resets the state machine and token object
	else if (stateMachine.getCurrentState() == 6)
	{
		token.changeType(DIGIT);
		stateMachine.resetState();
		token.changeLineNum(lineNum);
		return token;
	}
	// Prints a real token and resets the state machine and token object
	else if (stateMachine.getCurrentState() == 9)
	{
		token.changeType(REAL);
		stateMachine.resetState();
		token.changeLineNum(lineNum);
		return token;
	}
	else if (stateMachine.getCurrentState() == 7 || stateMachine.getCurrentState() == 13)
	{
		token.changeType(OPERATOR);
		stateMachine.resetState();
		token.changeLineNum(lineNum);
		return token;
	}
	// Invalid token. Resets state machine and clears the token object
	else
	{
		token.changeLexeme("");
		token.changeType(UNKNOWN);
		stateMachine.resetState();
		token.changeLineNum(lineNum);
		return token;
	}
}

// Clears the current token object
void Lexer::clearToken()
{
	token.changeLexeme("");
	token.changeType(UNKNOWN);
}

bool Lexer::lineEmpty()
{
	return emptyLine;
}