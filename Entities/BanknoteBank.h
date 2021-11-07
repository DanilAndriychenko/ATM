#pragma once
#include "JSONItem.h"
#include <unordered_map>

using Banknote = int;

class BanknoteBank
{
public:
	static BanknoteBank& getInstance()
	{
		static BanknoteBank instance(BANKNOTE_BANK_PATH);
		return instance;
	}

	~BanknoteBank() { save(); }

	const std::unordered_map<Banknote, int>& getBanknotesMap() const { return _availableBanknotes; }
	std::unordered_map<Banknote, int>& getBanknotesMap() { return _availableBanknotes; }
	//void setAvailableBanknotes(const std::unordered_map<Banknote, int>& map) { _availableBanknotes = map; }
	//should be called each time when ATM is powered off
	void save() const;
private: 
	BanknoteBank(const std::string& filePath);
	BanknoteBank(const BanknoteBank&) = delete;
	void operator=(const BanknoteBank&) = delete;
	std::unordered_map<Banknote, int> _availableBanknotes;
	rapidjson::Document _doc;
	std::string _filePath;
};