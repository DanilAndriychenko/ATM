#pragma once
#include "State.h"

class Authorization : public State
{
public:
    Authorization():State(_commandsForThisState){};
    ~Authorization() override{};
    Authorization(const Authorization& other) = delete;
    Authorization& operator=(const Authorization& other) = delete;

private:
    static ComsToPtrs _commandsForThisState;
};

void authorize(std::vector<utils::Args>);
