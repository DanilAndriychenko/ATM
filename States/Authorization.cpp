#include "Authorization.h"
#include "Maintenance.h"
#include "../Entities/ATM.h"
#include "../Entities/Cards.h"

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
    if (utils::isID(arguments[0], id) && utils::isPassword(arguments[1], password))
    {
        //todo get from BD
        //Cards<ClientCard> cardsStorage(CLIENTS_DB_PATH);
        // cardsStorage.findCardByNumber()
        ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(1, ClientCard::CardType::DEBIT, "John Smith", password, 1000, 11, 22));
        std::cout << "Authorized\n";
        return true;
    }
    return false;
}
