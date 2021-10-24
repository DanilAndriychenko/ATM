#pragma once
#include "JSONItem.h"
#include <iostream>

class Account : public JSONItem
{
public:
	Account(const int64_t, const int, const bool);
	virtual ~Account() {};
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

protected:
	const int64_t getID() const { return _id; }
	const int getPin() const { return _pin; }
	const bool isAdmin() const { return _isAdmin; }

private:
	const int64_t _id;
	const int _pin;
	const bool _isAdmin;
};


//throw exception in case of incorrect document
//const Account* findAccountByID(const int64_t, const rapidjson::Document&);

