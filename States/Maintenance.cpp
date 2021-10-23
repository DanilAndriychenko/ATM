#include "Maintenance.h"
#include <functional>
#include <iostream>


#include "Authorization.h"
#include "../Entities/ATMState.h"

Maintenance::ComsToPtrs Maintenance::_commandsForThisState
{
	{Command{"getTotal", "Authorizes you to ATM takes id and password as arguments"}, &Maintenance::getTotal}
};

std::shared_ptr<State> Maintenance::getNextState()
{
    std::cout << "movingToNextState\n";
	return std::make_shared<Authorization>();
}

bool Maintenance::getTotal(utils::Args arguments)
{
	std::cout << ATMState::getATMState().getTotalSumAsAdmin() << '\n';
	return false;
}
