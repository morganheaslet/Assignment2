#include "Lexer.h"
#include <iostream>
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

	std::cout << "while This is3 a t3st line. 0 42 55.5 55. + ++ +++ (taco) The Lexer should only reprint the valid tokens below." << std::endl;
	Lexer.getLine("while This is3 a t3st line. 0 42 55.5 55. + ++ +++ (taco) The Lexer should only reprint the valid tokens below.");
	Lexer.parseLine();

	system("pause");

	return 0;
}