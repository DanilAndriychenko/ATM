#pragma once
#include "Card.h"


class ClientCard final : public Card
{
public:
	enum class CardType
	{
		DEBIT = 0,
		CREDIT = 1
	};

	ClientCard(const int number, const CardType type, const std::string& name, const int pin, const int64_t balance, const int expMonth, const int expYear);

	static const std::shared_ptr<ClientCard> Deserialize(const rapidjson::Value& obj);

	const int64_t getBalance() const { return _balance; }
	const std::string& getName() const { return _name; }
	const int64_t getCreditLimit() const { return _creditLimit; }
	const std::pair<int, int>& getExpiryDate() const { return _expiryDate; }
	void setBalance(const int64_t balance) { _balance = balance; }
	void setName(const std::string& name) { _name = name; }
	bool setCreditLimit(const int64_t limit);
	bool isExpired() const;
	CardType getType() const { return _type; }

private:
	bool Serialize(rapidjson::Document&) const override;
	int64_t  _balance;
	int64_t _creditLimit;
	CardType _type;
	std::string _name;
	std::pair<int, int> _expiryDate;
	static const int64_t maxCreditLimit;
};
