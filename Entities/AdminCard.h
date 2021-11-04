#pragma once
#include "Card.h"

class AdminCard final : public Card
{
public:
	AdminCard(const int number, const int pin);
	~AdminCard() {}
	static const std::shared_ptr<AdminCard> Deserialize(const rapidjson::Value& obj);
private:
	bool Serialize(rapidjson::Document&) const override;
	//AdminCard(const int number, const int pin);
	
};

//std::ostream& operator<< (std::ostream& os, const AdminCard&);