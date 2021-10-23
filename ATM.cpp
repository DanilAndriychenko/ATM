#include "ATM.h"


#include "Entities/ATMState.h"
#include "States/Authorization.h"

// void ATM::printAvailableCommandsWithDescription(const Mode state) const
// {
// 	const auto availableCommands = _stateToAvailableCommands.at(state);
// 	cout << "/help - prints all available commands for this mode\n";
// 	for (auto availableCommand : availableCommands)
// 	{
// 		if (_commandToDescription.contains(availableCommand))
// 		{
// 			cout << _commandToDescription.at(availableCommand) << '\n';
// 		}
// 	}
// }
void ATM::turnOn()
{
    ATMState::getATMState().setCurrentState(std::make_shared<Authorization>());
}

void ATM::executeCommandIfExists(std::pair<std::string, utils::Args> input)
{
    if(ATMState::getATMState().getCurrentState()->executeCommandIfExists(input))
    {
        ATMState::getATMState().setCurrentState(ATMState::getATMState().getCurrentState()->getNextState());
    }
}
