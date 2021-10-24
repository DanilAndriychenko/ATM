#include "Entities/ATM.h"
#include "States/State.h"

#include <iostream>

using std::string;
using std::cout;

// Main is the function that called every time when ATM powered on
int main()
{
	ATM::getATM().listenCommands();
	return 0;
}
