#pragma once
#include "JSONItem.h"
#include <unordered_map>

using Banknote = int;

class BanknoteBank final : public JSONItem
{
public:
	BanknoteBank(const std::string& filePath);
	~BanknoteBank() {}
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

	const std::unordered_map<Banknote, int>& getAvailableBanknotes() const { return _availableBanknotes; }
	//void setAvailableBanknotes(const std::unordered_map<Banknote, int>& map) { _availableBanknotes = map; }

private:
	std::unordered_map<Banknote, int> _availableBanknotes;
	rapidjson::Document _doc;
};