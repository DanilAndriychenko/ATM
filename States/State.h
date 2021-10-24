#pragma once

#include "../Utils/Utils.h"

#include <memory>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class State
{
public:
	// If returns true then move to new state
	using CommandPtr = bool (*)(Args);
	struct CommandData;
	using CommandToDataMap = unordered_map<CommandName, CommandData>;

	explicit State(CommandToDataMap& commandToDataMap);
	State(const State& other) = delete;
	State& operator=(const State& other) = delete;
	virtual ~State() {};

	bool executeCommandIfExists(const ParsedInput& parsedInput) const;

	virtual std::shared_ptr<State> getNextState() = 0;
	void printAllCommands() const;
private:
	CommandToDataMap& _commandToDataMap;

	static bool help(Args);
};

struct State::CommandData
{
	string description;
	CommandPtr commandPtr;
};
