#define _CRT_SECURE_NO_WARNINGS
#include "ClientCard.h"
#include <time.h>

ClientCard::ClientCard(const int64_t number, const std::string& name, const int pin, const int64_t balance, const int expMonth, const int expYear) :
	Card(number, pin, false), _name(name), _balance(balance), _expiryDate(expMonth, expYear)
{}

bool ClientCard::Serialize(rapidjson::Document& doc) const
{
	auto& allocator = doc.GetAllocator();

	rapidjson::Value v;

	v.SetObject();

	v.AddMember("number", getNumber(), allocator);

	v.AddMember("name", rapidjson::StringRef(_name.c_str()), allocator);

	v.AddMember("balance", _balance, allocator);

	v.AddMember("pin", getPin(), allocator);

	v.AddMember("expMonth", _expiryDate.first, allocator);

	v.AddMember("expYear", _expiryDate.second, allocator);

	doc.PushBack(v, allocator);

	return true;
}

const std::shared_ptr<ClientCard> ClientCard::Deserialize(const rapidjson::Value& obj)
{
	return std::make_shared<ClientCard>(obj["number"].GetInt64(), 
									obj["name"].GetString(),
									obj["pin"].GetInt(),
									obj["balance"].GetInt64(),
									obj["expMonth"].GetInt(),
		                            obj["expYear"].GetInt());
}

bool ClientCard::isExpired() const
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	
	int month = 1 + aTime->tm_mon; 
	int year = aTime->tm_year + 1900;
	if(_expiryDate.second > year || (_expiryDate.second == year && _expiryDate.first > month))
		return true;
	return false;
}

//std::ostream& operator<< (std::ostream& os, const User& us)
//{
//	os << "User {\n" << "ID: " << us.getID() << "\nPIN: " << us.getPin() << "\nName: " << us.getName() << 
//		"\nBalance: " << us.getBalance() << '}';
//	return os;
//}