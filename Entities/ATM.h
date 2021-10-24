#pragma once
#include <memory>
#include <unordered_map>

#include "Banknotes.h"
#include "./../Utils/Utils.h"
#include "./../States/State.h"

class User;

// This class is a data storage
// for all initial ATM data(e.g. money available, current user)
class ATM
{
public:
	static ATM& getATM();

	void listenCommands();
	void executeCommandIfExists(const ParsedInput& parsedCommand);

	void setCurrentUser(const User&);
	User* getCurrentUser() { return _currentUser; }

	std::shared_ptr<State> getCurrentState() const { return _currentState; }

	/* Functions available only for money operating states */
	void getMoney(const Banknote, const int numberOfBanknotes) {};
	int getTotalSumAsAdmin() const { return 0; };
	int getNumOfBanknotesAvailable(const Banknote) const { return 0; };
	/* End of Functions available only for money operating states */

	void cashOut(const int sum) {};
	bool canCashOutSum() { return false; }

	void addMoney(const Banknote, const int numberOfBanknotes) {}

private:
	ATM();
	~ATM() {}

	const ATM& operator=(const ATM&) = delete;
	ATM(const ATM&) = delete;

	class User* _currentUser;
	class std::shared_ptr<State> _currentState;
	std::unordered_map<Banknote, int> _availableBanknotes;
};
