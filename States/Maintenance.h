#pragma once

#include "State.h"

class Maintenance final : public State
{
public:
	explicit Maintenance(): State(_commandsForThisState) {}
	Maintenance(const Maintenance& other) = delete;
	Maintenance& operator=(const Maintenance& other) = delete;
	~Maintenance() override {}

	std::shared_ptr<State> getNextState() override;

private:
	static CommandToDataMap _commandsForThisState;

	static bool getTotal(Args arguments);
};
