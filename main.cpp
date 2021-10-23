#include "ATM.h"
#include "States/State.h"
#include "Utilities/Utils.h"


using std::string;

// Main is the function that called every time when ATM powered on
int main(int argc, char* argv[])
{
	std::cout << "Hello\n";
    ATM atm{};
	atm.turnOn();
	std::string input;
	while(true)
	{
		std::getline(std::cin, input);
		std::pair<utils::functionName, utils::Args> parsedInput;
		parsedInput.first = utils::parseLine(input, parsedInput.second);
		utils::toLowerCase(parsedInput.first);
		atm.executeCommandIfExists(parsedInput);
	}

	
	return 0;
}