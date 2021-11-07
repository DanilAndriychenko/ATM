#pragma once
#include <unordered_map>
#include <set>

#include "JSONItem.h"

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

    int getNumOfBanknotes(const Banknote) const;
    int getTotal() const;
    void printBanknotesNum() const;
    void addBanknotes(const Banknote, const int);
    void cashOut(const Banknote, const int);
    
    static bool banknoteExists(const Banknote b) {return existingBanknotes.contains(b);}
    static void printAvailableBanknotes();
    static const std::set<int>& getAllAvailableBanknotes() {return existingBanknotes;}
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
    
    static const std::set<int> existingBanknotes;
};