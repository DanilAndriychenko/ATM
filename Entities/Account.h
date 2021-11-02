#pragma once
#include "JSONItem.h"
#include <iostream>

class Account : public JSONItem
{
public:
	Account(const int64_t id, const int pin, const bool isAdmin) : _id(id), _pin(pin), _isAdmin(isAdmin) {}
	virtual ~Account() {};

//protected:
	const int64_t getID() const { return _id; }
	const int getPin() const { return _pin; }
	const bool isAdmin() const { return _isAdmin; }

private:
	virtual bool Serialize(rapidjson::Document&) const = 0;
	const int64_t _id;
	const int _pin;
	const bool _isAdmin;
};

