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

const Admin* findAdminByID(const int64_t id, rapidjson::Document& doc)
{
	if (!doc.IsArray())
		return nullptr; //throw exception
	rapidjson::Value::ValueIterator itr = doc.GetArray().Begin();
	Admin* admin(nullptr);
	for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt64() == id)
		{
			admin = new Admin();
			admin->Deserialize(*itr);
			break;
		}
	}
	return admin;
}
