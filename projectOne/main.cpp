/*
  main.cpp
  projectOne
  CPSC323

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

//For FSM use
char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                    'X', 'Y', 'Z'},
    digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

string keywords[1] = { },
        operators[1] = { },
        separators[1] = { };

int main() {
    cout << "Please enter the source file name: ";
    string sourceName;
    cin >> sourceName;
    fstream fileStream;
    fileStream.open(sourceName + ".txt");
    if(fileStream.is_open())
    {
        cout << "File Opened Successfully.\n";
    }else{
        cout << "File not found.\n";
        return 0;
    }
    
    
    string line;
    while (getline(fileStream, line))
    {
        stringstream linestream(line);
        string token_str;
        while (getline(linestream, token_str, ' '))
        {
            // token_cstr now has the cstring version of the token
            char * token_cstr = new char[token_str.length()];
            strcpy (token_cstr, token_str.c_str());
            
            char * p = strtok(token_cstr,"\t\r\n ");
            while (p!=0)
            {
                cout << p << '\n';
                p = strtok(NULL,"\t\r\n ");
            }
            delete[] token_cstr;
            
            //cout <<  token << endl;
        }
    }
    fileStream.close();
    return 0;
}
