#include "User.h"

User::User() : _id(-1), _pin(0), _balance(0), _isAdmin(0), _name("")
{}

User::User(const int64_t id, const std::string& name, const int pin, const bool isAdm, const int64_t balance) :
	_id(id), _name(name), _pin(pin), _isAdmin(isAdm), _balance(balance)
{}

bool User::Deserialize(const rapidjson::Value& obj)
{
	setID(obj["id"].GetInt64());
	setPin(obj["pin"].GetInt());
	setBalance(obj["balance"].GetInt64());
	setIsAdmin(obj["isAdmin"].GetBool());
	setName(obj["name"].GetString());
	return true;
}

bool User::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("id");
	writer->Int64(_id);

	writer->String("name");
	writer->String(_name.c_str());

	writer->String("balance");
	writer->Int64(_balance);

	writer->String("pin");
	writer->Int(_pin);

	writer->String("isAdmin");
	writer->Bool(_isAdmin);

	writer->EndObject();

	return true;
}

