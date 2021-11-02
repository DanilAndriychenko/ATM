#include "User.h"

User::User(const int64_t id, const std::string& name, const int pin, const int64_t balance) :
	Account(id, pin, false), _name(name), _balance(balance)
{}


bool User::Serialize(rapidjson::Document& doc) const
{
	auto& allocator = doc.GetAllocator();

	rapidjson::Value v;

	v.SetObject();

	v.AddMember("id", getID(), allocator);

	v.AddMember("name", rapidjson::StringRef(getName().c_str()), allocator);

	v.AddMember("balance", getBalance(), allocator);

	v.AddMember("pin", getPin(), allocator);

	doc.PushBack(v, allocator);

	return true;
}

const std::shared_ptr<User> User::Deserialize(const rapidjson::Value& obj)
{
	return std::make_shared<User>(obj["id"].GetInt64(), 
									obj["name"].GetString(),
									obj["pin"].GetInt64(),
									obj["balance"].GetInt64());
}

//std::ostream& operator<< (std::ostream& os, const User& us)
//{
//	os << "User {\n" << "ID: " << us.getID() << "\nPIN: " << us.getPin() << "\nName: " << us.getName() << 
//		"\nBalance: " << us.getBalance() << '}';
//	return os;
//}