#include "ATMState.h"

ATMState& ATMState::getATMState()
{
	static ATMState singleton;
	return singleton;
}

ATMState::ATMState()
{
	
}
