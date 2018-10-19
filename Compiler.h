#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Lexer.h"

class Compiler
{
public:
	Compiler();
	Compiler(std::string inputFileName, std::string outputFileName);
	void CreateTokenList();
	void OutputTokenList();

private:
	std::string inputFile;  // Name of input file
	std::string outputFile; // Name of output file
	std::vector<Token> tokenList;
	int listLocation;
};

