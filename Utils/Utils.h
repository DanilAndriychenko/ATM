#pragma once

#include <string>
#include <vector>

using CommandName = std::string;
using Args = std::vector<std::string>;

struct ParsedInput
{
	CommandName commandName;
	Args args;
};

namespace utils
{
	const CommandName parseLine(const std::string& line, Args& tokenized);

	unsigned hashStr(const char* s);

	bool isDouble(const std::string& str);
	bool isInt(const std::string& str);

	void toLowerCase(std::string& str);
	
	const std::string getStringBuffer(const std::string& filePath);
}

/*namespace std
{
	template<> struct hash<const std::string>
	{
		std::size_t operator()(const std::string& commandName) const noexcept
		{
			return utils::hashStr(commandName.c_str());
		}
	};
}*/
struct StringHasher
{
	std::size_t operator()(const std::string& str) const noexcept
	{
		return utils::hashStr(str.c_str());
	}
};











/*
//		cout << "Maintenance mode.\n\
// 		You must have explicit, authorized permission to access or configure this device.\n\
// 		Unauthorized attempts and actions to access or use this system may result in civil and/or criminal penalties.\n\
// 		If this is the first launch of ATM, make sure to set apropretiate bank's name\n\
// 		and change password for defult addministrative account.\n";
// 		printAvailableCommandsWithDescription(_state);
 */

// void ATM::printAvailableCommandsWithDescription(const Mode state) const
// {
// 	const auto availableCommands = _stateToAvailableCommands.at(state);
// 	cout << "/help - prints all available commands for this mode\n";
// 	for (auto availableCommand : availableCommands)
// 	{
// 		if (_commandToDescription.contains(availableCommand))
// 		{
// 			cout << _commandToDescription.at(availableCommand) << '\n';
// 		}
// 	}
// }
// 	const map<Mode, vector<string>> _stateToAvailableCommands
// 	{
// 		{
// 			Mode::Maintenance,
// 			{
// 				"showBalance", "addBanknotes", "cashOutBanknotes", "putInIdle", "changeBanksName",
// 				"addAdminAcc", "editAdminAcc", "deleteAdminAcc"
// 			}
// 		}
// 	};
// 	const map<string, string> _commandToDescription
// 	{
// 		{
// 			"addBanknotes",
// 			"/addBanknotes {denomination} {quantity} - adds {quantity} banknotes of {denomination} to ATM. \
// 			 Command expects to recieve two integers."
// 		},
// 		{
// 			"cashOutBanknotes",
// 			"/cashOutBanknotes {denomination} {quantity} - cash out {quantity} banknotes of {denomination} from ATM. \
// 			 Command expects to recieve two integers."
// 		},
// 		{"putInIdle", "/putInIdle - Make ATM available and print init display."}
// 	};