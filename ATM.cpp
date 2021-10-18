#include "ATM.h"

void ATM::printAvailableCommandsWithDescription(const State state) const
{
	const auto availableCommands = _stateToAvailableCommands.at(state);
	for (auto availableCommand : availableCommands)
	{
		cout << _commandToDescription.at(availableCommand) << '\n';
	}
}
