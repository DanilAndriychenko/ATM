#include "Account.h"

Account::Account() : _id(0), _pin(0), _isAdmin(true) {}

Account::Account(const bool isAdm) : _id(0), _pin(0), _isAdmin(isAdm) {}

Account::Account(const int64_t id, const int pin, const bool isAdm) : _id(id), _pin(pin), _isAdmin(isAdm) {}

bool Account::Deserialize(const rapidjson::Value& obj)
{
	setID(obj["id"].GetInt64());
	setPin(obj["pin"].GetInt());
	return true;
}

bool Account::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("id");
	writer->Int64(_id);

	writer->String("pin");
	writer->Int(_pin);

	writer->EndObject();

	return true;
}

std::ostream& operator<< (std::ostream& os, const Account& acc)
{
	os << (acc.isAdmin() ? "Admin" : "User") << " {\n" << "ID: " << acc.getID() << "\nPIN: " << acc.getPin() << '}';
	return os;
}

const Account* findAccountByID(const int64_t id, const rapidjson::Document& doc)
{
	if (!doc.IsArray())
		return nullptr; //throw exception
	Account* admin(nullptr);
	for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt64() == id)
		{
			admin = new Account();
			admin->Deserialize(*itr);
			break;
		}
	}
	return admin;
}
