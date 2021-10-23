#pragma once
#include <string>
#include "../Utilities/Utils.h"

class StateMachine
{
public:
    void executeCommandIfExists(std::pair<std::string, utils::Args>);

private:
    class State* _currentState;    
};
