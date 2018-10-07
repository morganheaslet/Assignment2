#include "FSM.h"

// Initializer
FSM::FSM()
{
	// Unknown, character, digit, operator, real
	currentState = 1;
	previousState = 0;

};

void FSM::changeState(state characterType)
{
	previousState = currentState;
	currentState = fsmStateTable[previousState][int(characterType)];
};

int FSM::getCurrentState()
{
	return currentState;
}

int FSM::getPreviousState()
{
	return previousState;
}

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

void FSM::resetState()
{
	currentState = 1;
	previousState = 0;
}