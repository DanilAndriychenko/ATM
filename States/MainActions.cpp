#include "MainActions.h"

#include "Authorization.h"
#include "../Entities/ATM.h"
#include "../Entities/ClientCard.h"

MainActions::CommandToDataMap MainActions::_commandsForThisState
{
    {"showbalance", {"empty description", &MainActions::showBalance}},
    {"cashout", {"empty description", &MainActions::cashOut}},
    {"cashin", {"empty description", &MainActions::cashIn}},
    {"changepassword", {"empty description", &MainActions::changePassword}},
    {"transfermoneytoanotheraccount", {"empty description", &MainActions::transferMoneyToAnotherAccount}},
    {"transfermoneytophoneaccount", {"empty description", &MainActions::transferMoneyToPhoneAccount}},
    {"quite", {"empty description", &MainActions::quite}},
};

std::shared_ptr<State> MainActions::getNextState()
{
    return std::make_shared<Authorization>();
}

bool MainActions::showBalance(Args&)
{
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    std::cout << "Your balance is : " << card->getBalance() << '\n';
    return false;
}

bool MainActions::cashOut(Args& args)
{
    if (args.size() != 1)
    {
        std::cout << "cashOut function takes one argument\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "cashOut takes number as argument\n";
        return false;
    }
    
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    const int sum = std::stoi(args[0]);
    
    if (card->getBalance() < sum)
    {
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    if (ATM::getATM().cashOut(sum))
    {
        //todo rewrite using transactions
        card->setBalance(card->getBalance() - sum);
        std::cout << sum << " grivnas was successfully checked out\n";
        return false;
    }
    std::cout << "Sorry, ATM doesn't` have enough money to cash out the sum\n";
    return false;
}

bool MainActions::cashIn(Args& args)
{
    if(args.size() != 2)
    {
        std::cout << "cashIn function takes 2 arguments banknote and number of banknotes\n";
        return false;
    }
    if(!utils::isInt(args[0]))
    {        
        std::cout << "First argument is banknote value\nAvailable banknotes are: \n";
        BanknoteBank::printAvailableBanknotes();
        return false;
    }
    if(!utils::isInt(args[1]))
    {        
        std::cout << "Second argument is number of banknotes you want to cash in. Please enter integer value\n";
        BanknoteBank::printAvailableBanknotes();
        return false;
    }
    const Banknote banknote = std::stoi(args[0]);
    if(!BanknoteBank::banknoteExists(banknote))
    {
        std::cout << "There is no such a banknote " << banknote << '\n';
        std::cout << "Please enter one of existing ones\n";
        BanknoteBank::printAvailableBanknotes();
        return false;        
    }
    const int numOfBanknotes = std::stoi(args[1]);
    if(numOfBanknotes <= 0)
    {
        std::cout << "Second argument cannot be below zero. This is the number of banknotes you want to cash in\n";
        return false;
    }
    ATM::getATM().addMoney(banknote, numOfBanknotes);
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    card->setBalance(card->getBalance() + numOfBanknotes * banknote);
    std::cout << "You cashed in " << numOfBanknotes * banknote << " grivnas\n";;
    return false;
}

bool MainActions::changePassword(Args& args)
{
    if (args.size() != 1)
    {
        std::cout << "changePassword command takes 1 argument(new password)\n";
        return false;
    }
    int newPassword = std::stoi(args[0]);
    if(utils::isPassword(args[0], newPassword))
    {
        std::cout << "Password was successfully changed\n";
        return false;
    }
    return false;
}

bool MainActions::transferMoneyToAnotherAccount(Args& args)
{
    if(args.size() != 2)
    {
        std::cout << "transferMoneyToAnotherAccount function takes 2 arguments: amount of money you want to transfer and id of other account\n";
        return false;
    }
    if(!utils::isInt(args[0]))
    {        
        std::cout << "First argument is sum of money you want to transfer. It must be integer value\n";
        return false;
    }
    const int amountOfMoney = std::stoi(args[0]);
    if(amountOfMoney <= 0)
    {
        std::cout << "Amount of money you want to transfer has to be positive\n";
        return false;
    }
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    if(card->getBalance() < amountOfMoney)
    {        
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    int cardID = 0;
    if(!utils::isID(args[1], cardID))
    {
        return false;        
    }
    //todo check if this id exists
    if(false)
    {
        std::cout << "No such user found. Operation canceled\n";
        return false;
    }
    card->setBalance(card->getBalance() - amountOfMoney);
    std::cout << "Successfully transferred " << amountOfMoney << " grivnas to user " << cardID << '\n';
    //todo increase money of second user
    return false;
}

bool MainActions::transferMoneyToPhoneAccount(Args& args)
{
    if(args.size() != 2)
    {
        std::cout << "transferMoneyToAnotherAccount function takes 2 arguments: amount of money you want to transfer and phone number\n";
        return false;
    }
    if(!utils::isInt(args[0]))
    {        
        std::cout << "First argument is sum of money you want to transfer. It must be integer value\n";
        return false;
    }
    const int amountOfMoney = std::stoi(args[0]);
    if(amountOfMoney <= 0)
    {
        std::cout << "Amount of money you want to transfer has to be positive\n";
        return false;
    }
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    if(card->getBalance() < amountOfMoney)
    {        
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    if(!utils::matchPhoneNumber(args[1]))
    {
        std::cout << "Second argument has to be a phone number\n";
        return false;        
    }
    card->setBalance(card->getBalance() - amountOfMoney);
    std::cout << "Successfully transferred " << amountOfMoney << " grivnas to " << args[1] << '\n';
    return false;
}

