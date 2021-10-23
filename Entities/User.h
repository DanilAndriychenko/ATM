#pragma once

#include "JSONItem.h"

class User : public JSONItem
{
public:
	User();
	User(const int64_t, const std::string&, const int, const bool, const int64_t);
	virtual ~User() {}
	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	
	//getters / setters
	void setID(const int64_t id) { _id = id; }
	void setBalance(const int64_t bal) { _balance = bal; }
	void setIsAdmin(const bool isadm) { _isAdmin = isadm; }
	void setName(const std::string& na) { _name = na; }
	void setPin(const int pin) { _pin = pin; }

	const int64_t getID() const { return _id; }
	const int64_t getBalance() const { return _balance; }
	const std::string& getName() const { return _name; }
	const int getPIN() const { return _pin; }
	const bool getIsAdmin() { return _isAdmin; }

private:
	int64_t _id;
	int64_t  _balance;
	std::string _name;
	int _pin;
	bool _isAdmin;
};
