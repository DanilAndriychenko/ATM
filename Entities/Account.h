#pragma once
#include "JSONItem.h"
#include <iostream>

class Account : public JSONItem
{
public:
	Account(const int64_t, const int, const bool);
	virtual ~Account() = 0;

protected:
	const int64_t getID() const { return _id; }
	const int getPin() const { return _pin; }
	const bool isAdmin() const { return _isAdmin; }

private:
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	const int64_t _id;
	const int _pin;
	const bool _isAdmin;
};

