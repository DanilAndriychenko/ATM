#pragma once
#include "JSONItem.h"
#include <iostream>

class Admin : public JSONItem
{
public:
	Admin();
	Admin(const int64_t, const int);
	virtual ~Admin() {}
	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

	//getters / setters
	const int64_t getID() const { return _id; }
	const int getPin() const { return _pin; }

	void setID(const int64_t id) { _id = id; }
	void setPin(const int pin) { _pin = pin; }

private:
	int64_t _id;
	int _pin;
};
//throw exception in case of incorrect document
const Admin* findAdminByID(const int64_t, const rapidjson::Document&);

std::ostream& operator<< (std::ostream& os, const Admin&);