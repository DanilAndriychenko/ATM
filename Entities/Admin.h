#pragma once
#include "Account.h"

class Admin final : public Account
{
public:
	Admin(const int64_t, const int);
	~Admin() {}
	static const std::shared_ptr<Admin> Deserialize(const rapidjson::Value& obj);
};

//std::ostream& operator<< (std::ostream& os, const Admin&);