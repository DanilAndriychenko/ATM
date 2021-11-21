#include "Entities/ATM.h"
#include "States/State.h"

#include <iostream>

#include "Tests/Tester.h"

using std::string;
using std::cout;

#define NDEBUG

// Main is the function that called every time when ATM powered on
int main()
{
#ifndef NDEBUG
	Tester::runTests();
#endif
	ATM::getATM().listenCommands();
	return 0;
}
