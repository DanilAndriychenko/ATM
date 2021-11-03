#pragma once
#include "Card.h"


class ClientCard final : public Card
{
public:
	ClientCard(const int64_t number, const std::string& name, const int pin, const int64_t balance, const int expMonth, const int expYear);
	~ClientCard() {}

	static const std::shared_ptr<ClientCard> Deserialize(const rapidjson::Value& obj);

	const int64_t& getBalance() const { return _balance; }
	const std::string& getName() const { return _name; }
	const std::pair<int, int>& getExpiryDate() const { return _expiryDate; }
	void setBalance(const int64_t balance) { _balance = balance; }
	void setName(const std::string& name) { _name = name; }

	bool isExpired() const;

private:
	bool Serialize(rapidjson::Document&) const override;
	int64_t  _balance;
	std::string _name;
	std::pair<int, int> _expiryDate;
};

//std::ostream& operator<< (std::ostream&, const User&);