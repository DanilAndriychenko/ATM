#pragma once
#include "JSONItem.h"
#include <iostream>

class Card : public JSONItem
{
public:
	Card(const int64_t number, const int pin, const bool isAdmin) : _number(number), _pin(pin), _isAdmin(isAdmin) {}
	virtual ~Card() {};

//protected:
	const int64_t getNumber() const { return _number; }
	const int getPin() const { return _pin; }
	const bool isAdmin() const { return _isAdmin; }
	void setPin(const int pin) { _pin = pin; }

private:
	virtual bool Serialize(rapidjson::Document&) const = 0;
	int64_t _number;
	int _pin;
	bool _isAdmin;
};

