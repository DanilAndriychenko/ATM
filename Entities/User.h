#pragma once
#include "Admin.h"


class User : public Admin
{
public:
	User();
	User(const int64_t, const std::string&, const int, const int64_t);
	virtual ~User() {}
	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	
	//getters / setters
	void setBalance(const int64_t bal) { _balance = bal; }
	void setName(const std::string& na) { _name = na; }
	
	const int64_t getBalance() const { return _balance; }
	const std::string& getName() const { return _name; }

private:
	int64_t  _balance;
	std::string _name;
};

std::ostream& operator<< (std::ostream&, const User&);