#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

using std::cout;
using std::map;
using std::vector;
using std::string;

class ATM
{
private:
	enum class State { Maintenance, Idle, MenuActions };

public:
	void printAvailableCommandsWithDescription(State state) const;

	explicit ATM(const string nameOfBankToWhichATMBelongs): _state(State::Maintenance),
															_nameOfBankToWhichATMBelongs(nameOfBankToWhichATMBelongs)
	{
		cout << "ATM is in maintenance state.\n";
		printAvailableCommandsWithDescription(_state);
	}

private:
	const map<State, vector<string>> _stateToAvailableCommands
	{
		{State::Maintenance, {"addBanknotes", "cashOutBanknotes", "putInIdle"}}
	};
	const map<string, string> _commandToDescription
	{
		{"addBanknotes", "/addBanknotes {denomination} {quantity} - adds {quantity} banknotes of {denomination} to ATM. Command expects to recieve two integers."},
		{"cashOutBanknotes", "/cashOutBanknotes {denomination} {quantity} - cash out {quantity} banknotes of {denomination} from ATM. Command expects to recieve two integers."},
		{"putInIdle", "/putInIdle - Make ATM available and print init display."}
	};
	
	State _state;
	// We are making independent ATM that can belong to any of existing banks.
	string _nameOfBankToWhichATMBelongs;
};
