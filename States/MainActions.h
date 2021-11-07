#pragma once
#include "State.h"

class MainActions : public State
{
public:
    MainActions() : State(_commandsForThisState){}
    ~MainActions() override{}
    MainActions(const MainActions&) = delete;
    MainActions& operator=(const MainActions&) = delete;

    std::shared_ptr<State> getNextState() override;

private:
    static CommandToDataMap _commandsForThisState;

    //return value means if we need to go to next state 
    static bool quit(Args&) { return true; }
    static bool showBalance(Args&);
    static bool cashOut(Args&);
    static bool cashIn(Args&);
    static bool changePassword(Args&);
    static bool transferMoneyToAnotherAccount(Args&);
    static bool transferMoneyToPhoneAccount(Args&);
    static bool showTransactions(Args&);
};
