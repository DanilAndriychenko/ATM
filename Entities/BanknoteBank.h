#pragma once
#include "JSONItem.h"
#include <unordered_map>

using Banknote = int;

class BanknoteBank
{
public:
	BanknoteBank(const std::string& filePath);
	~BanknoteBank() {}

	const std::unordered_map<Banknote, int>& getAvailableBanknotes() const { return _availableBanknotes; }
	std::unordered_map<Banknote, int>& getAvailableBanknotes() { return _availableBanknotes; }
	//void setAvailableBanknotes(const std::unordered_map<Banknote, int>& map) { _availableBanknotes = map; }
	void save() const;
private: 
	std::unordered_map<Banknote, int> _availableBanknotes;
	rapidjson::Document _doc;
	std::string _filePath;
};