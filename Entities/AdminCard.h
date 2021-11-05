#pragma once
#include "Card.h"

class AdminCard final : public Card
{
public:
	AdminCard(const int number, const int pin);
	static const std::shared_ptr<AdminCard> Deserialize(const rapidjson::Value& obj);
	~AdminCard() {}
private:
	bool Serialize(rapidjson::Document&) const override;
};

//std::ostream& operator<< (std::ostream& os, const AdminCard&);