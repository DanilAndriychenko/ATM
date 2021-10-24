#include "State.h"
#include "../Entities/ATM.h"

#include <iostream>

State::State(CommandToDataMap& commandToDataMap): _commandToDataMap(commandToDataMap)
{
	commandToDataMap.insert({
		"help",
		{"shows all available commands and their descriptions", &State::help}
	});
}

bool State::executeCommandIfExists(ParsedInput& parsedInput) const
{
	if (_commandToDataMap.contains(parsedInput.commandName))
	{
		return _commandToDataMap.at(parsedInput.commandName).commandPtr(parsedInput.args);
	}

	std::cout << "Invalid command\n";
	return false;
}

void State::printAllCommands() const
{
	for (const auto& [fst, snd] : _commandToDataMap)
	{
		std::cout << fst << " - " << snd.description << '\n';
	}
}

bool State::help(Args&)
{
	ATM::getATM().getCurrentState()->printAllCommands();
	return false;
}
