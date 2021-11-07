#include "BanknoteBank.h"

const std::set<int> BanknoteBank::existingBanknotes{50, 100, 200, 500, 1000};

BanknoteBank::BanknoteBank(const std::string& filePath) : _availableBanknotes(), _doc(), _filePath(filePath)
{
    std::string bufferAdm = utils::getStringBuffer(filePath);
    InitDocument(bufferAdm, _doc);
    for (int i = 0; i < _doc.GetArray().Size(); i += 2)
    {
        _availableBanknotes.emplace(_doc.GetArray()[i].GetInt(), _doc.GetArray()[i + 1].GetInt());
    }
}

int BanknoteBank::getTotal() const
{
    int total = 0;
    for (const auto& bToNum : _availableBanknotes)
    {
        total += bToNum.second;
    }
    return total;
}

int BanknoteBank::getNumOfBanknotes(const Banknote b) const
{
    if(_availableBanknotes.contains(b))
        return _availableBanknotes.at(b);
    return 0;
}

void BanknoteBank::addBanknotes(const Banknote b, const int numToAdd)
{
    if(_availableBanknotes.contains(b))
    {
        _availableBanknotes.at(b) += numToAdd;
    }
    else
    {
        _availableBanknotes.emplace(b, numToAdd);
    }
}

void BanknoteBank::cashOut(const Banknote b, const int num)
{
    _availableBanknotes.at(b) -= num;
}

void BanknoteBank::printAvailableBanknotes()
{
    for (const auto& b : existingBanknotes)
    {
        std::cout << b << ' ';
    }
    std::cout << '\n';
}

void BanknoteBank::printBanknotesNum() const
{
    std::cout << "There are: \n";
    for (const auto& bToNum : _availableBanknotes)
    {
        std::cout << "\t" << bToNum.second << " banknotes of " << bToNum.second << "grivnas value\n";
    }
}

void BanknoteBank::save() const
{
    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.StartArray();
    for (std::pair<Banknote, int> p : _availableBanknotes)
    {
        writer.Int(p.first);
        writer.Int(p.second);
    }
    writer.EndArray();
    std::ofstream f(_filePath);

    f << buffer.GetString();
    f.flush();
    f.close();
}
