#include "Lexer.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstring>
#include <cctype>
#include <vector>

int main()
{
	std::string outputFileName;
	std::fstream inputFile;
	std::string inputFileName;
	std::string sourceString;
	
    std::cout << "Please enter the source file's absolute location: ";
    getline(std::cin, inputFileName);    
    inputFile.open(inputFileName);

    if(inputFile.is_open())
    {
        std::cout << "File Opened Successfully.\n";
    }else{
        std::cout << "File not found.\n";
        return 0;
    }    

	std::cout << "Please enter the output file name: ";
	getline(std::cin, outputFileName);
	Lexer Lexer(outputFileName);
	
    while(!inputFile.eof())
    {
		getline(inputFile,sourceString);
		Lexer.getLine(sourceString);
		Lexer.parseLine();
    }
	return 0;
}
