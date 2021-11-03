#include "AdminCard.h"

AdminCard::AdminCard(const int64_t number, const int pin) : Card(number, pin, true) {}

const std::shared_ptr<AdminCard> AdminCard::Deserialize(const rapidjson::Value& obj)
{
	return std::make_shared<AdminCard>(obj["number"].GetInt64(), obj["pin"].GetInt());
}

bool AdminCard::Serialize(rapidjson::Document& doc) const
{
	auto& allocator = doc.GetAllocator();

	rapidjson::Value v;

	v.SetObject();

	v.AddMember("number", getNumber(), allocator);

	v.AddMember("pin", getPin(), allocator);

	doc.PushBack(v, allocator);

	return true;
}

//std::ostream& operator<< (std::ostream& os, const AdminCard& ad)
//{
//	os << "AdminCard {\n" << "ID: " << ad.getID() << "\nPIN: " << ad.getPin() << '}';
//	return os;
//}