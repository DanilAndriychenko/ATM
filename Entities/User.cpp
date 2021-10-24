#include "User.h"

User::User(const int64_t id, const std::string& name, const int pin, const int64_t balance) :
	Account(id, pin, false), _name(name), _balance(balance)
{}


bool User::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("id");
	writer->Int64(getID());

	writer->String("name");
	writer->String(_name.c_str());

	writer->String("balance");
	writer->Int64(_balance);

	writer->String("pin");
	writer->Int(getPin());

	writer->EndObject();

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