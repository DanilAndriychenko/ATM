#include "Maintenance.h"
#include "Authorization.h"
#include "../Entities/ATM.h"

#include <iostream>

Maintenance::CommandToDataMap Maintenance::_commandToDataMap
{
	{"showBalance", {"empty description", &Maintenance::showBalance}},
	{"addBanknotes", {"empty description", &Maintenance::addBanknotes}},
	{"cashOutBanknotes", {"empty description", &Maintenance::cashOutBanknotes}},
	{"changeBanksName", {"empty description", &Maintenance::changeBanksName}},
	{"addAdminAcc", {"empty description", &Maintenance::addAdminAcc}},
	{"editAdminAcc", {"empty description", &Maintenance::editAdminAcc}},
	{"deleteAdminAcc", {"empty description", &Maintenance::deleteAdminAcc}},
	{"quit", {"empty description", &Maintenance::quit}},
};

std::shared_ptr<State> Maintenance::getNextState()
{
	std::cout << "movingToNextState\n";
	return std::make_shared<Authorization>();
}

bool Maintenance::showBalance(Args&) { return false; }
bool Maintenance::addBanknotes(Args&) { return false; }
bool Maintenance::cashOutBanknotes(Args&) { return false; }
bool Maintenance::quit(Args&) { return false; }
bool Maintenance::changeBanksName(Args&) { return false; }
bool Maintenance::addAdminAcc(Args&) { return false; }
bool Maintenance::editAdminAcc(Args&) { return false; }
bool Maintenance::deleteAdminAcc(Args&) { return false; }
