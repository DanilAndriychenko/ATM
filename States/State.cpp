#include "State.h"

bool operator==(const State::Command& lhs, const State::Command& rhs)
{
	return lhs.name == rhs.name;
}

State::Command::operator int() const
{
	return utils::hashStr(name.c_str());
}
