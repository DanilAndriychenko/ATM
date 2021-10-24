#pragma once

#include <memory>

#include "../Utils/Utils.h"

#include <string>
#include <map>

using std::map;
using std::string;

class State
{
public:
	// If returns true then move to new state
	using CommandPtr = bool (*)(Args);
	struct CommandData;
	// TODO here should be unordered_map, but there is problem with contains function
	using CommandToDataMap = map<CommandName, CommandData>;

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
