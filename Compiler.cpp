#include "Compiler.h"

Compiler::Compiler()
{
	listLocation = 0;
}

Compiler::Compiler(std::string inputFileName, std::string outputFileName)
{
	outputFile = outputFileName;
	inputFile = inputFileName;
}

void Compiler::CreateTokenList()
{
	std::fstream iFile;
	std::string sourceString;
	Token tempToken;
	Lexer ourLexer;

	iFile.open(inputFile);

	if (!iFile.is_open())
	{
		std::cout << "File not found.\n";
	}
	else
	{
		while (!iFile.eof())
		{
			if (ourLexer.lineEmpty())
			{
				getline(iFile, sourceString);
				ourLexer.getLine(sourceString);
			}

			tempToken = ourLexer.getToken();
			ourLexer.clearToken();

			if (tempToken.getLexeme() != "")
			{
				tokenList.push_back(tempToken);
				tempToken.changeLexeme("");
				tempToken.changeType(UNKNOWN);
			}			
		}
	}
}

void Compiler::OutputTokenList()
{
	Token tempToken;
	for (std::vector<Token>::const_iterator i = tokenList.begin(); i != tokenList.end(); i++)
	{
		tempToken = *i;
		std::cout << tempToken.getLexeme() << " " << tempToken.GetTypeString() << std::endl;
	}
}