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
	int fsmStateTable[14][5] =
	{
	{0,0,0,0,0},
	{12,5,6,7,12},
	{12,5,12,12,12},
	{12,6,12,12,12},
	{12,12,7,12,12},
	{12,5,10,12,12},
	{12,12,6,12,8},
	{12,12,12,13,12},
	{12,12,9,12,12},
	{12,12,9,12,12},
	{12,11,10,12,12},
	{12,11,10,12,12},
	{12,12,12,12,12},
	{12,12,12,12,12}
	};
	int currentState;
	int previousState;
};
