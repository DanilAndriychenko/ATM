#include "ATM.h"
#include "./../States/Authorization.h";

#include <iostream>

ATM& ATM::getATM()
{
	static ATM singleton;
	return singleton;
}

void ATM::listenCommands()
{
	std::string input;
	while (true)
	{
		std::getline(std::cin, input);
		if (input.empty())
		{
			std::cout << "Invalid command\n";
			continue;
		}
		ParsedInput parsedInput{};
		parsedInput.commandName = utils::parseLine(input, parsedInput.args);
		utils::toLowerCase(parsedInput.commandName);
		executeCommandIfExists(parsedInput);
	}
}

void ATM::executeCommandIfExists(ParsedInput& parsedCommand)
{
	if (_currentState->executeCommandIfExists(parsedCommand))
	{
		_currentState = _currentState->getNextState();
	}
}

ATM::ATM(): _currentUser(nullptr), _currentState{std::make_shared<Authorization>()}
{
	
}
