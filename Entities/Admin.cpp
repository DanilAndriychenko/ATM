#include "Admin.h"

Admin::Admin() : _id(0), _pin(0) {}

Admin::Admin(const int64_t id, const int pin) : _id(id), _pin(pin) {}

bool Admin::Deserialize(const rapidjson::Value& obj)
{
	setID(obj["id"].GetInt64());
	setPin(obj["pin"].GetInt());
	return true;
}

bool Admin::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("id");
	writer->Int64(_id);

	writer->String("pin");
	writer->Int(_pin);

	writer->EndObject();

	return true;
}

std::ostream& operator<< (std::ostream& os, const Admin& adm)
{
	os << "Admin {\n" << "ID: " << adm.getID() << "\nPIN: " << adm.getPin() << '}';
	return os;
}

