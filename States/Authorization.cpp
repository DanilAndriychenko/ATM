#include "Authorization.h"
#include "Maintenance.h"

#include <iostream>

Authorization::CommandToDataMap Authorization::_commandsForThisState
{
	{
		"auth",
		{
			"Authorizes you to ATM takes id and password as arguments",
			&Authorization::authorize
		}
	}
};

std::shared_ptr<State> Authorization::getNextState()
{
	std::cout << "movingToNextState\n";
	return std::make_shared<Maintenance>();
}

bool Authorization::authorize(Args arguments)
{
	if (arguments.size() == 2 && utils::isInt(arguments[0]) && utils::isInt(arguments[1]))
	{
		int id = std::stoi(arguments[0]);
		int password = std::stoi(arguments[1]);
		std::cout << "Authorized\n";
		return true;
	}
	std::cout << "Authorize function takes two arguments id and password\n";
	return false;
}
