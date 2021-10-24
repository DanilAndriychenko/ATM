#pragma once

#include "State.h"

class Maintenance final : public State
{
public:
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
	/* End of Functions managing money in ATM */

	// Transfer to authorize state
	static bool quit(Args&);
	
	/* Functions managing bank settings and admin accounts */
	static bool changeBanksName(Args&);
	static bool addAdminAcc(Args&);
	static bool editAdminAcc(Args&);
	static bool deleteAdminAcc(Args&);
	/* End of Functions managing admin accounts */
};
