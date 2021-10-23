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
public:
    void TurnOn(){};

private:
    class State* _currentState;
};

// class ATM
// {
// private:
// 	enum class Mode { Maintenance, Idle, MenuActions };
// 	enum class AccessRights { User, Admin };
// 	struct Account
// 	{
// 		string login;
// 		string encryptedPassword;
// 		AccessRights accessRights;
// 	};
//
// public:
// 	void printAvailableCommandsWithDescription(Mode state) const;
//
// 	explicit ATM(): _state(Mode::Maintenance)
// 	{
// 		// Востановить всю инфу из файла
// 		// TODO пофиксить чтобы строки выводились ровно от левого края.
// 		cout << "Maintenance mode.\n\
// 		You must have explicit, authorized permission to access or configure this device.\n\
// 		Unauthorized attempts and actions to access or use this system may result in civil and/or criminal penalties.\n\
// 		If this is the first launch of ATM, make sure to set apropretiate bank's name\n\
// 		and change password for defult addministrative account.\n";
// 		printAvailableCommandsWithDescription(_state);
// 		// Waiting for input
// 		std::getchar();
// 	}
//
// private:
// 	// TODO stateToAvailableCommands и commandToDescription считывать из файла
// 	// а если не будет существовать такого мода или команды то выводить
// 	// "Command unsupported by hardware"
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
//
// 	Mode _state;
// 	string _nameOfBankToWhichATMBelongs;
// 	vector<Account> _accounts;
//
//
// 	// Нужно хранить путь к файлу с конфигом,
// 	// считать его в формате джейсон например и распихать по мапам, векторам и переменным
// };
