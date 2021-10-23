#pragma once

#include <memory>

#include "../Utilities/Utils.h"

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class State
{
public:
	//if returns true the move to new state
	using CommandPtr = bool (*)(utils::Args);
	struct Command
	{
		Command(string commandName) : name(commandName){}
		Command(string commandName, string commandDescription) : name(commandName), description(commandDescription)
		{
			utils::toLowerCase(name);
		}
		
		string name;
		string description;
	};
	using ComsToPtrs = unordered_map<Command, CommandPtr>;
	
	
	explicit State(ComsToPtrs& comsToDesc);
	State(const State& other) = delete;
	State& operator=(const State& other) = delete;
	virtual ~State(){};

	bool executeCommandIfExists(std::pair<std::string, utils::Args>);

	virtual std::shared_ptr<State> getNextState() = 0;
	void printAllStates();

private:
	ComsToPtrs& _commandsToPtrs;

	static bool help(utils::Args);
};

bool operator==(const State::Command&, const State::Command&);

namespace std
{
	template<> struct hash<State::Command>
	{
		std::size_t operator()(State::Command const& s) const noexcept
		{
			return utils::hashStr(s.name.c_str());
		}
	};
}