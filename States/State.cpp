#include "State.h"

#include <iostream>

#include "../Entities/ATMState.h"

State::State(ComsToPtrs& comsToDesc): _commandsToPtrs(comsToDesc)
{
	comsToDesc.insert({Command("help", "shows all available commands and their descriptions"), &State::help});
}

bool State::executeCommandIfExists(std::pair<std::string, utils::Args> parsedInput)
{
	if(_commandsToPtrs.contains(parsedInput.first))
	{
		return _commandsToPtrs[parsedInput.first](parsedInput.second);
	}
	else
	{
		std::cout << "Invalid command\n";
		return false;
	}
}

void State::printAllStates()
{
	for(auto& kv : _commandsToPtrs) {
		std::cout << kv.first.name << " " << kv.first.description << '\n';
	} 
}

bool State::help(utils::Args)
{
	ATMState::getATMState().getCurrentState()->printAllStates();
	return false;
}

bool operator==(const State::Command& lhs, const State::Command& rhs)
{
	for(int i = 0; i < lhs.name.size(); i++)
	{
		if(std::tolower(lhs.name[i]) != std::tolower(rhs.name[i]))
		{
			return false;
		}
	}
	return true;
}
