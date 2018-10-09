#include <string>
#include <iostream>
#include <vector>
#include "state.h"

class FSM
{
public:
	FSM();
	void changeState(state characterType);
	int getCurrentState();
	int getPreviousState();
	void outputTable();
	void resetState();

private:
	// Below is the FSM table Each row is a machine state, and each column is the type of input being received
	// UNKNOWN, LETTER, DIGIT, OPERATOR, REAL ('.')
	int fsmStateTable[14][5] =
	{
	{0,0,0,0,0},             // Element 0 unused for readability
	{12,5,6,7,12},			 // State 1 (beginning state)
	{12,5,12,12,12},		 // State 2
	{12,6,12,12,12},		 // State 3
	{12,12,7,12,12},		 // State 4
	{12,5,10,12,12},		 // State 5
	{12,12,6,12,8},			 // State 6
	{12,12,12,13,12},		 // State 7
	{12,12,9,12,12},		 // State 8
	{12,12,9,12,12},		 // State 9
	{12,11,10,12,12},		 // State 10
	{12,11,10,12,12},		 // State 11
	{12,12,12,12,12},		 // State 12 (invalid state)
	{12,12,12,12,12}		 // State 13
	};
	int currentState;
	int previousState;
};
