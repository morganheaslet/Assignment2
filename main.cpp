#include "Compiler.h"
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
	std::string inputFileName;
		
    std::cout << "Please enter the source file's absolute location: ";
    getline(std::cin, inputFileName);    
	
	std::cout << "Please enter the output file name: ";
	getline(std::cin, outputFileName);
	Compiler ourCompiler(inputFileName, outputFileName);

	ourCompiler.CreateTokenList();

	ourCompiler.ParseTokenList();

	return 0;
}
