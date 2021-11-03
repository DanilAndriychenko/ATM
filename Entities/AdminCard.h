#pragma once
#include "Card.h"

class AdminCard final : public Card
{
public:
	AdminCard(const int64_t, const int);
	~AdminCard() {}
	static const std::shared_ptr<AdminCard> Deserialize(const rapidjson::Value& obj);
private:
	bool Serialize(rapidjson::Document&) const override;
};

//std::ostream& operator<< (std::ostream& os, const AdminCard&);