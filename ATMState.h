#pragma once
#include <unordered_map>

#include "Banknotes.h"

class User;
//This class is a data storage
//for all initial ATM data(e.g. money available, current user)
class final ATMState
{
public:
	ATMState& getATMState();

	void setCurrentUser(const User&);
	User* getCurrentUser() { return _currentUser;}

	void addMoneyAsAdmin(Banknote, int numberOfBanknotes);
	void getMoneyAsAdmin(Banknote, int numberOfBanknotes);

private:
	ATMState();
	~ATMState(){}

	const ATMState& operator=(const ATMState&) = delete;
	ATMState(const ATMState&) = delete;

	class User* _currentUser;
	std::unordered_map<Banknote, int> _availableBanknotes;
};
