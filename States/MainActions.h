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

    static bool quite(Args&) { return false; }
    static bool showBalance(Args&) { return false; }
    static bool cashOut(Args&) { return false; }
    static bool cashIn(Args&) { return false; }
    static bool changePassword(Args&) { return false; }
    static bool transferMoneyToAnotherAccount(Args&) { return false; }
    static bool transferMoneyToPhoneAccount(Args&) { return false; }
};
