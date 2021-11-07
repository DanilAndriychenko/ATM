#pragma once
#include <memory>
#include <unordered_map>


#include "BanknoteBank.h"
#include "./../Utils/Utils.h"
#include "./../States/State.h"

class User;

//static constexpr std::string BanknotesStoragePath = "../Resources/banknotes.json";

// This class is a data storage
// for all initial ATM data(e.g. money available, current user)
class ATM
{
public:
	static ATM& getATM();

	void listenCommands();
	void executeCommandIfExists(ParsedInput& parsedCommand);

	void setCurrentUser(const User&);
	User* getCurrentUser() { return _currentUser; }

	std::shared_ptr<State> getCurrentState() const { return _currentState; }

	void cashOut(const Banknote, const int numberOfBanknotes);
	void cashOut(const int sum);
	void addMoney(const Banknote, const int);
	int getTotal() const;
	void printBanknotesNumber(const Banknote) const;
	void printBanknotesNumber() const;


private:
	ATM();
	~ATM() {}

	bool getSumAsBanknotes(int sum, std::unordered_map<Banknote, int>&);

	const ATM& operator=(const ATM&) = delete;
	ATM(const ATM&) = delete;

	class User* _currentUser;
	class std::shared_ptr<State> _currentState;
	BanknoteBank& _availableBanknotes;
};
