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
	Lexer Lexer;
    std::cout << "Please enter the source file's absolute location: ";
    std::string sourceName, sourceString;
    getline(std::cin, sourceName);
    std::fstream fileStream;
    fileStream.open(sourceName);
    if(fileStream.is_open())
    {
        std::cout << "File Opened Successfully.\n";
    }else{
        std::cout << "File not found.\n";
        return 0;
    }
    
    freopen( "./output_file.txt", "w", stdout );
    while(!fileStream.eof())
    {
    getline(fileStream, sourceString);
	Lexer.getLine(sourceString);
	Lexer.parseLine();
    }

	return 0;
}
