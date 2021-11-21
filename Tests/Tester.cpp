#include "Tester.h"

#include "../Entities/CardManager.h"
#include "../Entities/ATM.h"
#include "../Entities/Transaction.h"
#include "../States/Authorization.h"
#include "../States/MainActions.h"
#include "../States/Maintenance.h"

#include <cmath>

void Tester::runTests()
{
    authenticateExistingUser();
    authenticateAdmin();
    authenticateUnknownCardNumber();
    
    testAdminCashingIn();
    testAdminCashOut();
    
    testClientCashIn();
    testClientCashOut();
    
    testExpiredCard();
    selfTransaction();
    testNotEnoughMoneyCase();
    testOurBankTransactionCommission();
    testAnotherBankTransactionCommission();
}

void Tester::authenticateExistingUser()
{
    std::vector<ClientCard> allClientCards;
    ClientCardManager::getInstance().findAllCards(allClientCards);
    ClientCard* clientWithNotExpiredCard = nullptr;
    for(auto& cc : allClientCards)
    {
        if(!cc.isExpired())
        {
            clientWithNotExpiredCard = &cc;
        }
    }
    if(clientWithNotExpiredCard == nullptr)
    {
        return;
    }
    std::vector args{std::to_string(clientWithNotExpiredCard->getNumber()), std::to_string(clientWithNotExpiredCard->getPin())};
    Authorization::authorize(args);
    assert(Authorization::authorize(args) && ATM::getATM().getCurrentCard() != nullptr);
}

void Tester::authenticateAdmin()
{
    std::vector<AdminCard> allAdminCards;
    AdminCardManager::getInstance().findAllCards(allAdminCards);
    std::vector args{std::to_string(allAdminCards[0].getNumber()), std::to_string(allAdminCards[0].getPin())};
    assert(Authorization::authorize(args) && ATM::getATM().getCurrentCard() == nullptr);
}

void Tester::authenticateUnknownCardNumber()
{
    std::vector<AdminCard> allAdminCards;
    AdminCardManager::getInstance().findAllCards(allAdminCards);
    std::vector<std::string> args{"85855", "8888"};
    assert(Authorization::authorize(args) == false && ATM::getATM().getCurrentCard() == nullptr);
}

void Tester::testAdminCashingIn()
{
    const int total = ATM::getATM().getTotal();
    std::vector<std::string> args{"500", "3"};
    Maintenance::addBanknotes(args);
    assert(ATM::getATM().getTotal() == total + 500 * 3);
}

void Tester::testAdminCashOut()
{
    const int total = ATM::getATM().getTotal();
    std::vector<std::string> args{"500", "3"};
    Maintenance::cashOutBanknotes(args);
    assert(ATM::getATM().getTotal() == total - 500 * 3);
}

void Tester::testClientCashIn()
{
    std::vector<ClientCard> allClientCards;
    ClientCardManager::getInstance().findAllCards(allClientCards);
    ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(allClientCards[0]));
    const int total = allClientCards[0].getBalance();
    std::vector<std::string> args{"500", "3"};
    MainActions::cashIn(args);   
    
    assert(total < ATM::getATM().getCurrentCard()->getBalance());
}

void Tester::testClientCashOut()
{
    std::vector<ClientCard> allClientCards;
    ClientCardManager::getInstance().findAllCards(allClientCards);
    ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(allClientCards[0]));
    const int total = allClientCards[0].getBalance();
    std::vector<std::string> args{"1500"};
    MainActions::cashOut(args);
    assert(total > ATM::getATM().getCurrentCard()->getBalance());
}

void Tester::testExpiredCard()
{
    const ClientCard cc{11111, ClientCard::CardType::DEBIT, "ds", 1111, 142, 10, 2020};
    assert(cc.isExpired());
}

void Tester::selfTransaction()
{
    ClientCard cc{11111, ClientCard::CardType::DEBIT, "s", 1111, 10000, 11, 2025};
    const Transaction transaction(Transaction::TransactionType::CARD_TRANSFER, &cc, 10, cc.getNumber());
    assert(transaction.getErrorMessage() == "Sender cannot be receiver simultaneously");
}

void Tester::testNotEnoughMoneyCase()
{
    ClientCard cc{11111, ClientCard::CardType::DEBIT, "s", 1111, 1, 11, 2025};
    const Transaction transaction(Transaction::TransactionType::CARD_TRANSFER, &cc, 100, 111);
    assert(transaction.getErrorMessage() == "Insufficient funds for transfer");
}

void Tester::testOurBankTransactionCommission()
{
    std::vector<ClientCard> allClientCards;
    ClientCardManager::getInstance().findAllCards(allClientCards);
    ClientCard* ourBankClient = nullptr;
    for(auto& cc : allClientCards)
    {
        if(Transaction::bankID == cc.getNumber() % 1000)
        {
            ourBankClient = &cc;
        }
    }
    if(ourBankClient == nullptr)
    {
        return;
    }
    ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(*ourBankClient));
    const int total =ourBankClient->getBalance();
    std::vector<std::string> args{"500", "3"};
    MainActions::cashIn(args);
    assert(total + 500 * 3 == ATM::getATM().getCurrentCard()->getBalance());
    args = {"1500"};
    MainActions::cashOut(args);
    assert(total == ATM::getATM().getCurrentCard()->getBalance());
}

void Tester::testAnotherBankTransactionCommission()
{
    std::vector<ClientCard> allClientCards;
    ClientCardManager::getInstance().findAllCards(allClientCards);
    ClientCard* anotherBankClient = nullptr;
    for(auto& cc : allClientCards)
    {
        if(Transaction::bankID != cc.getNumber() % 1000)
        {
            anotherBankClient = &cc;
        }
    }
    if(anotherBankClient == nullptr)
    {
        return;
    }
    ATM::getATM().setCurrentCard(std::make_shared<ClientCard>(*anotherBankClient));
    int total = anotherBankClient[0].getBalance();
    std::vector<std::string> args{"500", "3"};
    MainActions::cashIn(args);
    assert(total + 500 * 3 - round(0.025 * (500 * 3)) == ATM::getATM().getCurrentCard()->getBalance());
    total = total + 500 * 3 - round(0.025 * (500 * 3));
    args = {"1500"};
    MainActions::cashOut(args);
    assert(total - round(1.025 * (500 * 3)) - 1 == ATM::getATM().getCurrentCard()->getBalance());
}
