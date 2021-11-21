#pragma once

#include "State.h"

class Maintenance final : public State
{
public:
	friend class Tester;
	
	explicit Maintenance(): State(_commandToDataMap) {}
	Maintenance(const Maintenance& other) = delete;
	Maintenance& operator=(const Maintenance& other) = delete;
	~Maintenance() override {}

	std::shared_ptr<State> getNextState() override;
private:
	static CommandToDataMap _commandToDataMap;

	/* Functions managing money in ATM */
	static bool showBalance(Args&);
	static bool addBanknotes(Args&);
	static bool cashOutBanknotes(Args&);
	static bool showBanknotesNum(Args&);
	/* End of Functions managing money in ATM */

	// Transfer to authorize state
	static bool quit(Args&);
	static bool turnOffATM(Args&);
};
