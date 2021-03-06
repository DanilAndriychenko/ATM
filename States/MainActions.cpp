#include "MainActions.h"

#include <memory>

#include "Authorization.h"
#include "../Entities/ATM.h"
#include "../Entities/TransactionManager.h"
#include "../Entities/ClientCard.h"

MainActions::CommandToDataMap MainActions::_commandsForThisState
{
    {"showbalance", {"prints user`s balance", &MainActions::showBalance}},
    {"cashout", {"cashes out sum of money", &MainActions::cashOut}},
    {"cashin", {"cashes in certain number of banknotes", &MainActions::cashIn}},
    {"changepassword", {"empty description", &MainActions::changePassword}},
    {"transfermoneytoanotheraccount", {"empty description", &MainActions::transferMoneyToAnotherAccount}},
    {"transfermoneytocharity", {"transfers money to charity", &MainActions::transferMoneyToCharity}},
    {
        "transfermoneytophoneaccount",
        {"transfers money to account of other bank user", &MainActions::transferMoneyToPhoneAccount}
    },
    {"showtransactions", {"prints the list of all user transactions", &MainActions::showTransactions}},
    {"changecreditlimit", {"if card is credit changes credit limit", &MainActions::changeCreditLimit}},
    {"showcreditlimit", {"if card is credit displays credit limit", &MainActions::showCreditLimit}},
    {"quit", {"returns to authorization state", &MainActions::quit}}
};

std::shared_ptr<State> MainActions::getNextState()
{
    return std::make_shared<Authorization>();
}

bool MainActions::showBalance(Args&)
{
    ClientCard* card = &*ATM::getATM().getCurrentCard();
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

    ClientCard* card = &*ATM::getATM().getCurrentCard();

    const int sum = std::stoi(args[0]);
    std::unordered_map<Banknote, int> res;
    if (ATM::getATM().getSumAsBanknotes(sum, res))
    {
        std::shared_ptr<Transaction> tr = TransactionManager::getInstance().makeTransaction(
            Transaction::TransactionType::CASH_OUT, card, sum);
        tr->print(std::cout);
        if (tr->isSuccessfull())
        {
            std::cout << '\n';
            ATM::getATM().cashOut(sum);
        }
        return false;
    }
    std::cout << "Sorry, ATM doesn't have enough money to cash out the sum\n";
    return false;
}

bool MainActions::cashIn(Args& args)
{
    if (args.size() != 2)
    {
        std::cout << "cashIn function takes 2 arguments banknote and number of banknotes\n";
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
        std::cout << "Second argument is number of banknotes you want to cash in. Please enter integer value\n";
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
    ClientCard* card = &*ATM::getATM().getCurrentCard();
    TransactionManager::getInstance().makeTransaction(Transaction::TransactionType::CASH_IN, card, numOfBanknotes * banknote)
                               ->print(std::cout);
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
    if (utils::isPassword(args[0], newPassword))
    {
        std::cout << "Password was successfully changed\n";
        ClientCard* cc = &*ATM::getATM().getCurrentCard();
        cc->setPin(newPassword);
        ClientCardManager::getInstance().modifyCardData(*cc);
        return false;
    }
    return false;
}

bool MainActions::transferMoneyToAnotherAccount(Args& args)
{
    if (args.size() != 2)
    {
        std::cout <<
            "transferMoneyToAnotherAccount function takes 2 arguments: amount of money you want to transfer and id of other account\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "First argument is sum of money you want to transfer. It must be integer value\n";
        return false;
    }
    const int amountOfMoney = std::stoi(args[0]);
    if (amountOfMoney <= 0)
    {
        std::cout << "Amount of money you want to transfer has to be positive\n";
        return false;
    }
    ClientCard* card = &*ATM::getATM().getCurrentCard();
  
    int cardID = 0;
    if (!utils::isID(args[1], cardID))
    {
        return false;
    }
    TransactionManager::getInstance().makeTransaction(Transaction::TransactionType::CARD_TRANSFER, card, amountOfMoney,
                                                cardID)->print(std::cout);
    return false;
}

bool MainActions::transferMoneyToPhoneAccount(Args& args)
{
    if (args.size() != 2)
    {
        std::cout <<
            "transferMoneyToAnotherAccount function takes 2 arguments: amount of money you want to transfer and phone number\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "First argument is sum of money you want to transfer. It must be integer value\n";
        return false;
    }
    const int amountOfMoney = std::stoi(args[0]);
    if (amountOfMoney <= 0)
    {
        std::cout << "Amount of money you want to transfer has to be positive\n";
        return false;
    }
    ClientCard* card = &*ATM::getATM().getCurrentCard();
 
    if (!utils::matchPhoneNumber(args[1]))
    {
        std::cout << "Second argument has to be a phone number\n";
        return false;
    }
    TransactionManager::getInstance().makeTransaction(card, amountOfMoney, args[1])->print(std::cout);
    return false;
}

bool MainActions::transferMoneyToCharity(Args& args)
{
    if (args.size() != 1)
    {
        std::cout <<
            "transferMoneyToCharity function takes 1 arguments: amount of money you want to transfer\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "First argument is sum of money you want to transfer. It must be integer value\n";
        return false;
    }
    const int amountOfMoney = std::stoi(args[0]);
    if (amountOfMoney <= 0)
    {
        std::cout << "Amount of money you want to transfer has to be positive\n";
        return false;
    }
    ClientCard* card = &*ATM::getATM().getCurrentCard();
    TransactionManager::getInstance().makeTransaction(Transaction::TransactionType::CHARITY_TRANSFER, card, amountOfMoney)->
                                print(std::cout);
    return false;
}

bool MainActions::showTransactions(Args& args)
{
    int numOfTransactionsToDisplay = 0;
    if (args.size() == 1 && utils::isInt(args[0]))
    {
        numOfTransactionsToDisplay = std::stoi(args[0]) + 1;
    }

    std::vector<Transaction> res;
    TransactionManager::getInstance().findTransactionsByClientNumber(res, ATM::getATM().getCurrentCard()->getNumber());
    if(numOfTransactionsToDisplay <= 0 || numOfTransactionsToDisplay > res.size())
    {
        numOfTransactionsToDisplay = res.size();
    }
    for (int i = res.size() - 1; i > res.size() - numOfTransactionsToDisplay; i--)
    {
        res[i].print(std::cout);
    }
    if (res.size() == 0)
    {
        std::cout << "There is no transactions yet\n";
    }
    return false;
}

bool MainActions::showCreditLimit(Args&)
{
    ClientCard* cc = &*ATM::getATM().getCurrentCard();
    if (cc->getType() == ClientCard::CardType::CREDIT)
    {
        std::cout << cc->getCreditLimit() << '\n';
        return false;
    }
    std::cout << "Debit cards don` have credit limit\n";
    return false;
}

bool MainActions::changeCreditLimit(Args& args)
{
    if (args.size() != 1)
    {
        std::cout << "changeCreditLimit function takes 1 arguments: new credit limit\n";
        return false;
    }
    if (!utils::isInt(args[0]))
    {
        std::cout << "First argument is  new credit limit. It must be integer value\n";
        return false;
    }
    const int limit = std::stoi(args[0]);
    if (limit <= 0)
    {
        std::cout << "Credit limit has to be positive\n";
        return false;
    }
    ClientCard* cc = &*ATM::getATM().getCurrentCard();
    std::cout << cc->setCreditLimit(limit) << '\n';
    return false;
}
