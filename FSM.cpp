#include "FSM.h"

// Constructor
FSM::FSM()
{
	currentState = 1;
	previousState = 0;
};

// Uses the FSM table to change the current state based off the type of input it receives
void FSM::changeState(state characterType)
{
	previousState = currentState;
	currentState = fsmStateTable[previousState][int(characterType)];
};

// Returns currrent state
int FSM::getCurrentState()
{
	return currentState;
}

// Returns previous state
int FSM::getPreviousState()
{
	return previousState;
}

// Outputs the state table
void FSM::outputTable()
{
	for (unsigned int i = 0; i < 13; i++)
	{
		std::cout << "State " << i << ": ";
		for (unsigned int t = 0; t < 5; t++)
		{
			std::cout << fsmStateTable[i][t] << " ";
		}
		std::cout << std::endl;
	}
}

// Resets the state machine
void FSM::resetState()
{
	currentState = 1;
	previousState = 0;
}