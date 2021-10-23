#pragma once
#include <memory>
#include <unordered_map>

#include "Banknotes.h"
class ATM;

class State;
class User;
//This class is a data storage
//for all initial ATM data(e.g. money available, current user)
class ATMState
{
public:
	static ATMState& getATMState();

	void setCurrentUser(const User&);
	User* getCurrentUser() { return _currentUser;}

	std::shared_ptr<State> getCurrentState() {return _currentState;}

	/*Functions available only for money operating states*/
	void getMoney(const Banknote, const int numberOfBanknotes){};
	int getTotalSumAsAdmin() const {return 0;};
	int getNumOfBanknotesAvailable(const Banknote) const {return 0;};	
	/*End of Functions available only for money operating states*/

	void cashOut(const int sum){};
	bool canCashOutSum(){return false;}
	
	void addMoney(const Banknote, const int numberOfBanknotes){}

	friend class ATM;

private:
	ATMState();
	~ATMState(){}

	const ATMState& operator=(const ATMState&) = delete;
	ATMState(const ATMState&) = delete;

	class User* _currentUser;
    class std::shared_ptr<State> _currentState;
	std::unordered_map<Banknote, int> _availableBanknotes;

	
	void setCurrentState(std::shared_ptr<State> newState) {_currentState = newState;}
};
