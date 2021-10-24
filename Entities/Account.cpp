#include "Account.h"

Account::Account(const int64_t id, const int pin, const bool isAdmin) : _id(id), _pin(pin), _isAdmin(isAdmin) {}

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

//const Account* findAccountByID(const int64_t id, const rapidjson::Document& doc)
//{
//	if (!doc.IsArray())
//		return nullptr; //throw exception
//	Account* admin(nullptr);
//	for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
//	{
//		if ((*itr)["id"].GetInt64() == id)
//		{
//			admin = new Account();
//			admin->Deserialize(*itr);
//			break;
//		}
//	}
//	return admin;
//}
