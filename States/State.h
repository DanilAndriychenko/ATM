#pragma once

#include "../Utilities/Utils.h"

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class State
{
public:
	using CommandPtr = void (*)(utils::Args);
	struct Command;
	using ComsToPtrs = unordered_map<Command, CommandPtr>;
	explicit State(ComsToPtrs& comsToDesc): _commandsToPtrs(comsToDesc) {}
	State(const State& other) = delete;
	State& operator=(const State& other) = delete;
	virtual ~State() = 0;

private:
	ComsToPtrs& _commandsToPtrs;
};

struct State::Command
{
	string name;
	string description;

	explicit operator int() const;
};

bool operator==(State::Command&, State::Command&);
