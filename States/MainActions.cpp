#include "MainActions.h"

#include <memory>

#include "Authorization.h"
#include "../Entities/ATM.h"
#include "../Entities/Transactions.h"
#include "../Entities/ClientCard.h"

MainActions::CommandToDataMap MainActions::_commandsForThisState
{
    {"showbalance", {"prints user`s balance", &MainActions::showBalance}},
    {"cashout", {"cashes out sum of money", &MainActions::cashOut}},
    {"cashin", {"cashes in certain number of banknotes", &MainActions::cashIn}},
    {"changepassword", {"empty description", &MainActions::changePassword}},
    {"transfermoneytoanotheraccount", {"empty description", &MainActions::transferMoneyToAnotherAccount}},
    {"transferMoneyToCharity", {"transfers money to charity", &MainActions::transferMoneyToCharity}},
    {
        "transfermoneytophoneaccount",
        {"transfers money to account of other bank user", &MainActions::transferMoneyToPhoneAccount}
    },
    {"showtransactions", {"prints the list of all user transactions", &MainActions::showTransactions}},
    {"changecreditlimit", {"if card is credit changes credit limit", &MainActions::changeCreditLimit}},
    {"showCreditLimit", {"if card is credit displays credit limit", &MainActions::showCreditLimit}},
    {"quit", {"returns to authorization state", &MainActions::quit}}
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
    std::unordered_map<Banknote, int> res;
    if (ATM::getATM().getSumAsBanknotes(sum, res))
    {
        std::shared_ptr<Transaction> tr = Transactions::getInstance().makeTransaction(
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
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    Transactions::getInstance().makeTransaction(Transaction::TransactionType::CASH_IN, card, numOfBanknotes * banknote)
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
        ClientCard* cc = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
        cc->setPin(newPassword);
        ClientCards::getInstance().modifyCardData(*cc);
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
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    if (card->getBalance() < amountOfMoney)
    {
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    int cardID = 0;
    if (!utils::isID(args[1], cardID))
    {
        return false;
    }
    Transactions::getInstance().makeTransaction(Transaction::TransactionType::CARD_TRANSFER, card, amountOfMoney,
                                                cardID);
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
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    if (card->getBalance() < amountOfMoney)
    {
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    if (!utils::matchPhoneNumber(args[1]))
    {
        std::cout << "Second argument has to be a phone number\n";
        return false;
    }
    Transactions::getInstance().makeTransaction(Transaction::TransactionType::PHONE_TRANSFER, card, amountOfMoney)->
                                print(std::cout);
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
    ClientCard* card = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    if (card->getBalance() < amountOfMoney)
    {
        std::cout << "Not enough money on your balance\n";
        return false;
    }
    Transactions::getInstance().makeTransaction(Transaction::TransactionType::CHARITY_TRANSFER, card, amountOfMoney)->
                                print(std::cout);
    return false;
}

bool MainActions::showTransactions(Args& args)
{
    std::vector<Transaction> res;
    Transactions::getInstance().findTransactionsByClientNumber(res, ATM::getATM().getCurrentCard()->getNumber());
    for (const auto& transaction : res)
    {
        transaction.print(std::cout);
    }
    if (res.size() == 0)
    {
        std::cout << "There is no transactions yet\n";
    }
    return false;
}

bool MainActions::showCreditLimit(Args&)
{
    ClientCard* cc = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
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
    ClientCard* cc = dynamic_cast<ClientCard*>(&*ATM::getATM().getCurrentCard());
    std::cout << cc->setCreditLimit(limit) << '\n';
    return false;
}
