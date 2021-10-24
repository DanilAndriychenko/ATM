#pragma once
#include "Account.h"


class User : public Account
{
public:
	User(const int64_t, const std::string&, const int, const int64_t);
	virtual ~User() {}

	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	static const std::shared_ptr<User> Deserialize(const rapidjson::Value& obj);


	const int64_t getBalance() const { return _balance; }
	const std::string& getName() const { return _name; }

private:
	const int64_t  _balance;
	const std::string _name;
};

//std::ostream& operator<< (std::ostream&, const User&);