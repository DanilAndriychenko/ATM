#include "User.h"

User::User() : Account(false), _balance(0), _name("")
{}

User::User(const int64_t id, const std::string& name, const int pin, const int64_t balance) :
	Account(id, pin, false), _name(name), _balance(balance)
{}

bool User::Deserialize(const rapidjson::Value& obj)
{
	setID(obj["id"].GetInt64());
	setPin(obj["pin"].GetInt());
	setBalance(obj["balance"].GetInt64());
	setName(obj["name"].GetString());
	return true;
}

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

std::ostream& operator<< (std::ostream& os, const User& us)
{
	os << "User {\n" << "ID: " << us.getID() << "\nPIN: " << us.getPin() << "\nName: " << us.getName() << 
		"\nBalance: " << us.getBalance() << '}';
	return os;
}