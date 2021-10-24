#include "Admin.h"

Admin::Admin(const int64_t id, const int pin) : Account(id, pin, true) {}

const std::shared_ptr<Admin> Admin::Deserialize(const rapidjson::Value& obj)
{
	return std::make_shared<Admin>(obj["id"].GetInt64(), obj["pin"].GetInt());
}

//std::ostream& operator<< (std::ostream& os, const Admin& ad)
//{
//	os << "Admin {\n" << "ID: " << ad.getID() << "\nPIN: " << ad.getPin() << '}';
//	return os;
//}