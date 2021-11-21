#include "Maintenance.h"
#include "Authorization.h"
#include "../Entities/ATM.h"

#include <iostream>

Maintenance::CommandToDataMap Maintenance::_commandToDataMap
{
    {"showbalance", {"prints total sum available in ATM", &Maintenance::showBalance}},
    {"addbanknotes", {"Adds banknotes to ATM", &Maintenance::addBanknotes}},
    {"cashoutbanknotes", {"Cashes out banknotes from ATM", &Maintenance::cashOutBanknotes}},
    {"showbanknotesnum", {"Displays number of banknotes for each available banknote", &Maintenance::showBanknotesNum}},
    {"quit", {"Returns to authentication state", &Maintenance::quit}},
    {"turnoff", {"Terminates the work of ATM", &Maintenance::quit}},
};

std::shared_ptr<State> Maintenance::getNextState()
{
    return std::make_shared<Authorization>();
}

bool Maintenance::showBalance(Args&)
{
    std::cout << "Total amount of money in ATM: " << ATM::getATM().getTotal() << '\n';
    return false;
}

bool Maintenance::addBanknotes(Args& args)
{
    if (args.size() != 2)
    {
        std::cout << "addBanknotes takes two arguments: banknote and number of banknotes\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "First argument is banknote value\nAvailable banknotes are: \n";
        BanknoteBank::printAvailableBanknotes();
        return false;
    }
    if (!utils::isInt(args[1]))
    {
        std::cout << "Second argument is number of banknotes you want to add. Please enter integer value\n";
        BanknoteBank::printAvailableBanknotes();
        return false;
    }
    const Banknote banknote = std::stoi(args[0]);
    if (!BanknoteBank::banknoteExists(banknote))
    {
        std::cout << "There is no such a banknote " << banknote << '\n';
        std::cout << "Please enter one of existing ones\n";
        BanknoteBank::printAvailableBanknotes();
        return false;
    }
    const int numOfBanknotes = std::stoi(args[1]);
    if (numOfBanknotes <= 0)
    {
        std::cout << "Second argument cannot be below zero. This is the number of banknotes you want to cash in\n";
        return false;
    }
    ATM::getATM().addMoney(banknote, numOfBanknotes);
    std::cout << "Successfully added money\n";
    return false;
}

bool Maintenance::cashOutBanknotes(Args& args)
{
    if (args.size() != 2)
    {
        std::cout << "cashOutBanknotes function takes two argument\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "cashOutBanknotes takes number as first argument\n";
        return false;
    }
    const int sum = std::stoi(args[0]);
    if (ATM::getATM().cashOut(sum))
    {
        return false;
    }
    std::cout << "Sorry, ATM doesn't have enough banknotes\n";
    return false;
}

bool Maintenance::showBanknotesNum(Args&)
{
    ATM::getATM().printBanknotesNumber();
    return false;
}

bool Maintenance::turnOffATM(Args&)
{
    ATM::getATM().turnOff();
    return false;
}

bool Maintenance::quit(Args&) { return true; }
