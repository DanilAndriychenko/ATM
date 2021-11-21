#include "Authorization.h"
#include "Maintenance.h"
#include "../Entities/ATM.h"
#include "../Entities/CardManager.h"

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
    if (ATM::getATM().getCurrentCard())
    {
        return std::make_shared<MainActions>();
    }
    return std::make_shared<Maintenance>();
}

bool Authorization::authorize(Args& arguments)
{
    if (arguments.size() != 2)
    {
        std::cout << "Authorize function takes two arguments id and password\n";
        return false;
    }
    int id, password;
    if (utils::isID(arguments[0], id) && utils::isPassword(arguments[1], password))
    {
        if (const std::shared_ptr<ClientCard> card = ClientCardManager::getInstance().findCardByNumber(id))
        {
            if (card->getPin() != password)
            {
                std::cout << "Incorrect password\n";
                return false;
            }
            if (card->isExpired())
            {
                std::cout << "Sorry your card is expired\n";
                return false;
            }
            ATM::getATM().setCurrentCard(card);
            std::cout << "Welcome " << card->getName() << "!\n";
            return true;
        }
        if (const std::shared_ptr<AdminCard> card = AdminCardManager::getInstance().findCardByNumber(id))
        {
            if (card->getPin() != password)
            {
                std::cout << "Incorrect password\n";
                return false;
            }
            std::cout << "Authorized with exclusive rights\n";
            ATM::getATM().setCurrentCard(nullptr);
            return true;
        }
        std::cout << "No such card\n";
    }
    return false;
}
