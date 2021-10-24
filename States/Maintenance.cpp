#include "Maintenance.h"
#include "Authorization.h"
#include "../Entities/ATM.h"

#include <iostream>

Maintenance::CommandToDataMap Maintenance::_commandsForThisState
{
	{
		"getTotal",
		{
			"desc not writen yet",
			&Maintenance::getTotal
		}
	}
};

std::shared_ptr<State> Maintenance::getNextState()
{
	std::cout << "movingToNextState\n";
	return std::make_shared<Authorization>();
}

bool Maintenance::getTotal(Args& arguments)
{
	std::cout << ATM::getATM().getTotalSumAsAdmin() << '\n';
	return false;
}
