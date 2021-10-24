#pragma once
#include "JSONItem.h"
#include <unordered_map>

using Banknote = int;

class BanknoteBank : public JSONItem
{
public:
	BanknoteBank();
	virtual ~BanknoteBank() {}

	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

	const std::unordered_map<Banknote, int>& getAvailableBanknotes() const { return _availableBanknotes; }
	void setAvailableBanknotes(const std::unordered_map<Banknote, int>& map) { _availableBanknotes = map; }

private:
	std::unordered_map<Banknote, int> _availableBanknotes;
};