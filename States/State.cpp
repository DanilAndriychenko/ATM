#include "State.h"
#include "../Entities/ATM.h"
#include <regex>
#include <iostream>

State::State(CommandToDataMap& commandToDataMap): _commandToDataMap(commandToDataMap)
{
	commandToDataMap.insert({
		"help",
		{"shows all available commands and their descriptions", &State::help}
	});
}


std::pair<std::string, int> State::getCommandFromPrefix(const std::string& userComm) const
{
	int cnt = 0;
	std::string command("");
	for (const auto& p : _commandToDataMap)
	{
		if (userComm.length() > p.first.length())
			continue;
		auto res = std::mismatch(userComm.begin(), userComm.end(), (p.first).begin());
		if (res.first == userComm.end())
		{
			cnt++;
			command = p.first;
		}
	}
	return std::make_pair(command, cnt);
}
bool State::executeCommandIfExists(ParsedInput& parsedInput) const
{
	auto pir = getCommandFromPrefix(parsedInput.commandName);

	if(pir.second == 1)
		return _commandToDataMap.at(pir.first).commandPtr(parsedInput.args);
	if(pir.second > 1)
		std::cout << "Incomplete command\n";
	else
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
