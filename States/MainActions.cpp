#include "MainActions.h"

#include "Authorization.h"

MainActions::CommandToDataMap MainActions::_commandsForThisState
{
    {"showBalance", {"empty description", &MainActions::showBalance}},
    {"cashOut", {"empty description", &MainActions::cashOut}},
    {"cashIn", {"empty description", &MainActions::cashIn}},
    {"changePassword", {"empty description", &MainActions::changePassword}},
    {"transferMoneyToAnotherAccount", {"empty description", &MainActions::transferMoneyToAnotherAccount}},
    {"transferMoneyToPhoneAccount", {"empty description", &MainActions::transferMoneyToPhoneAccount}},
    {"quite", {"empty description", &MainActions::quite}},
};

std::shared_ptr<State> MainActions::getNextState()
{
    return std::make_shared<Authorization>();
}
