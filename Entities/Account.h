#pragma once
#include "JSONItem.h"
#include <iostream>

class Account : public JSONItem
{
public:
	Account();
	Account(const bool);
	Account(const int64_t, const int, const bool);
	virtual ~Account() {}
	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

	//getters / setters
	const int64_t getID() const { return _id; }
	const int getPin() const { return _pin; }
	const bool isAdmin() const { return _isAdmin; }

	void setID(const int64_t id) { _id = id; }
	void setPin(const int pin) { _pin = pin; }
	void setIsAdmin(const bool adm) { _isAdmin = adm; }

private:
	int64_t _id;
	int _pin;
	bool _isAdmin;
};
//throw exception in case of incorrect document
const Account* findAccountByID(const int64_t, const rapidjson::Document&);

std::ostream& operator<< (std::ostream& os, const Account&);