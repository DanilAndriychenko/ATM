#pragma once
#include "State.h"

class Authorization : public State
{
public:
    Authorization():State(_commandsForThisState){};
    ~Authorization() override{};
    Authorization(const Authorization& other) = delete;
    Authorization& operator=(const Authorization& other) = delete;

    std::shared_ptr<State> getNextState() override;

private:
    static CommandToDataMap _commandsForThisState;
    
    static bool authorize(Args);
};

