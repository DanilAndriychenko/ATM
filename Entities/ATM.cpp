#include "ATM.h"
#include "./../States/Authorization.h";

#include <iostream>

ATM& ATM::getATM()
{
    static ATM singleton;
    return singleton;
}

void ATM::listenCommands()
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Invalid command\n";
            continue;
        }
        ParsedInput parsedInput{};
        parsedInput.commandName = utils::parseLine(input, parsedInput.args);
        utils::toLowerCase(parsedInput.commandName);
        executeCommandIfExists(parsedInput);
    }
}

void ATM::executeCommandIfExists(ParsedInput& parsedCommand)
{
    if (_currentState->executeCommandIfExists(parsedCommand))
    {
        _currentState = _currentState->getNextState();
    }
}

void ATM::cashOut(const Banknote b, const int numberOfBanknotes)
{
    if (!BanknoteBank::banknoteExists(b))
    {
        std::cout << "There is no such banknote as " << b << '\n';
        BanknoteBank::printAvailableBanknotes();
    }
    else if (_availableBanknotes.getNumOfBanknotes(b) < numberOfBanknotes || numberOfBanknotes < 0)
    {
        std::cout << "Invalid number of banknotes\n";
        std::cout << "ATM has " << _availableBanknotes.getNumOfBanknotes(b) << " banknotes of " << b << " value\n";
    }
    else
    {
        _availableBanknotes.cashOut(b, numberOfBanknotes);
    }
}

int ATM::getTotal() const
{
    return _availableBanknotes.getTotal();
}

void ATM::printBanknotesNumber(const Banknote b) const
{
    _availableBanknotes.getNumOfBanknotes(b);
}

void ATM::printBanknotesNumber() const
{
    _availableBanknotes.printBanknotesNum();
}

void ATM::addMoney(const int banknote, const int numberOfBanknotes)
{
    if (BanknoteBank::banknoteExists(banknote))
    {
        _availableBanknotes.addBanknotes(banknote, numberOfBanknotes);
    }
    else
    {
        std::cout << "there is no such banknote as " << banknote << '\n';
        BanknoteBank::printAvailableBanknotes();
    }
}

ATM::ATM(): _currentCard(nullptr), _currentState{std::make_shared<Authorization>()},
            _availableBanknotes(BanknoteBank::getInstance())
{
}

bool ATM::getSumAsBanknotes(int sum, std::unordered_map<Banknote, int>& sumInBanknotes)
{
    const std::set<int>& allBanknotes = BanknoteBank::getAllAvailableBanknotes();
    for (auto rit = allBanknotes.rbegin(); rit != allBanknotes.rend(); ++rit)
    {
        if (sum >= *rit)
        {
            const int numOfBanknotesForSum = sum / *rit;
            const int maxNumOfBanknotesAvailable = _availableBanknotes.getNumOfBanknotes(*rit);
            if (numOfBanknotesForSum <= maxNumOfBanknotesAvailable)
            {
                sumInBanknotes.at(*rit) = numOfBanknotesForSum;
                sum -= numOfBanknotesForSum * *rit;
            }
            else
            {
                sumInBanknotes.at(*rit) = maxNumOfBanknotesAvailable;
                sum -= maxNumOfBanknotesAvailable * *rit;
            }
        }
    }
    return sum == 0;
}

void ATM::cashOut(int sum)
{
    std::unordered_map<Banknote, int> sumInBanknotes;
    if(getSumAsBanknotes(sum, sumInBanknotes))
    {
        for (auto& bToNum : sumInBanknotes)
        {
            _availableBanknotes.cashOut(bToNum.first, bToNum.second);
        }
    }
    else
    {
        std::cout << "Sorry the sum is not available.\n";
    }
}
