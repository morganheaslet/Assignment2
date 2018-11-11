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
	void ParseTokenList();
	void OutputTokenList();
	void Rat18F();
	void OptFuncDef();
	void FuncDef();
	void Function();
	void OptParameterList();
	void ParameterList();
	void Parameter();
	void Qualifier();
	void Body();
	void OptDeclarationList();
	void DeclarationList();
	void Declaration();
	void IDs();
	void StatementList();
	void Statement();
	void Compound();
	void Assign();
	void If();
	void Return();
	void Print();
	void Scan();
	void While();
	void Condition();
	void Relop();
	void Expression();
	void Term();
	void Factor();
	void Primary();
	void Empty();
	void Error(std::string error);

private:
	std::string inputFile;  // Name of input file
	std::string outputFile; // Name of output file
	std::ofstream oFile;
	std::vector<Token> tokenList;
	std::vector<Token>::iterator iter;
	int listLocation;
	bool printFunctions = true;
	int tokenPosition;
};

