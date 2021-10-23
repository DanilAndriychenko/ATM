#include "Authorization.h"

#include <iostream>

#include "Maintenance.h"

Authorization::ComsToPtrs Authorization::_commandsForThisState
{
    {Command{"a", "Authorizes you to ATM takes id and password as arguments"}, &Authorization::authorize}
};

std::shared_ptr<State> Authorization::getNextState()
{
    std::cout << "movingToNextState\n";
    return std::make_shared<Maintenance>();
}

bool Authorization::authorize(utils::Args arguments)
{
    int id, password;
    if(arguments.size() == 2 && utils::is_int(arguments[0]) && utils::is_int(arguments[1]))
    {
        id = std::stoi(arguments[0]);
        password = std::stoi(arguments[1]);
        std::cout << "Authorized\n";
        return true;
    }
        std::cout << "Authorize function takes two arguments id and password\n";
        return false;
}
