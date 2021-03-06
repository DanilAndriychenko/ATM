#pragma once
#include <memory>
#include <unordered_map>

#include "BanknoteBank.h"
#include "Card.h"
#include "ClientCard.h"
#include "./../Utils/Utils.h"
#include "./../States/State.h"

//static constexpr std::string BanknotesStoragePath = "../Resources/banknotes.json";

// This class is a data storage
// for all initial ATM data(e.g. money available, current user)
class ATM
{
public:
	static ATM& getATM();

	void listenCommands();
	void executeCommandIfExists(ParsedInput& parsedCommand);

	void setCurrentCard(const std::shared_ptr<ClientCard> с) { _currentCard = с; }
	std::shared_ptr<ClientCard> getCurrentCard() { return _currentCard; }

	std::shared_ptr<State> getCurrentState() const { return _currentState; }

	void cashOut(const Banknote, const int numberOfBanknotes);
	bool cashOut(const int sum);
	void addMoney(const Banknote, const int);
	long getTotal() const;
	void printBanknotesNumber(const Banknote) const;
	void printBanknotesNumber() const;
	bool getSumAsBanknotes(int sum, std::unordered_map<Banknote, int>&);
	void turnOff() {bIsActive = false;}


private:
	ATM();
	~ATM() {}

	const ATM& operator=(const ATM&) = delete;
	ATM(const ATM&) = delete;

	std::shared_ptr<ClientCard> _currentCard;
	class std::shared_ptr<State> _currentState;
	BanknoteBank& _availableBanknotes;

	bool bIsActive;
};
