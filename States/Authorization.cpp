#include "Authorization.h"
#include "Maintenance.h"
#include "../Entities/ATM.h"

#include <iostream>


#include "MainActions.h"
#include "../Entities/Card.h"
#include "../Entities/ClientCard.h"

Authorization::CommandToDataMap Authorization::_commandsForThisState
{
    {
        "authenticate",
        {
            "Authorizes you to ATM(takes id and password as arguments)",
            &Authorization::authorize
        }
    }
};

std::shared_ptr<State> Authorization::getNextState()
{
#ifdef NDEBUG
    std::cout << "movingToNextState\n";
#endif
    if(ATM::getATM().getCurrentCard()->isAdmin())
    {
        return std::make_shared<Maintenance>();        
    }
    return std::make_shared<MainActions>();
}

bool Authorization::authorize(Args& arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Authorize function takes two arguments id and password\n";
        return false;
    }
    int id, password;
    if (isID(arguments[0], id) && isPassword(arguments[1], password))
    {
        //todo get from BD
        ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(1, ClientCard::CardType::DEBIT, "John Smith", password, 1000, 11, 22));
        std::cout << "Authorized\n";
        return true;
    }
    return false;
}

bool Authorization::isID(std::string& idString, int& result)
{
    if (utils::isInt(idString))
    {
        const int id = std::stoi(idString);
        const int numOfDigits = id / pow(10, numOfDigitsInLogin - 1);
        if (numOfDigits > 0 && numOfDigits < 10)
        {
            result = id;
            return true;
        }
        std::cout << "ID must contain 5 digits\n";
        return false;
    }
    std::cout << "ID can contain only digits\n";
    return false;
}

bool Authorization::isPassword(std::string& passwordString, int& res)
{
    if (utils::isInt(passwordString))
    {
        const int id = std::stoi(passwordString);
        const int numOfDigits = id / pow(10, numOfDigitsInPassword - 1);
        if (numOfDigits > 0 && numOfDigits < 10)
        {
            res = id;
            return true;
        }
        std::cout << "Password must contain 4 digits\n";
        return false;
    }
    std::cout << "Password can contain only digits\n";
    return false;
}
