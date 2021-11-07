#define _CRT_SECURE_NO_WARNINGS
#include "ClientCard.h"
#include <time.h>

const int64_t ClientCard::maxCreditLimit(100000);

ClientCard::ClientCard(const int number, const CardType type, const std::string& name, const int pin,
                       const int64_t balance, const int expMonth, const int expYear) :
    Card(number, pin, false),
    _name(name),
    _balance(balance),
    _expiryDate(expMonth, expYear),
    _type(type),
    _creditLimit(0)
{
}

std::string ClientCard::setCreditLimit(const int64_t limit)
{
    if (_type != CardType::CREDIT)
    {
        return "Cannot set credit limit for debit card";
    }
    if (limit > maxCreditLimit)
    {
        return "The value is too high. Max credit limit is " + std::to_string(maxCreditLimit);
    }
    _creditLimit = limit;
    return "Credit limit successfully set";
}

bool ClientCard::Serialize(rapidjson::Document& doc) const
{
    auto& allocator = doc.GetAllocator();

    rapidjson::Value v;

    v.SetObject();

    v.AddMember("number", getNumber(), allocator);

    v.AddMember("type", static_cast<int>(_type), allocator);

    //v.AddMember("name", rapidjson::StringRef(getName().c_str()), allocator);

    v.AddMember("name", rapidjson::Value(_name.c_str(), allocator).Move(), allocator);

    v.AddMember("balance", _balance, allocator);

    v.AddMember("pin", getPin(), allocator);

    if (_type == CardType::CREDIT)
        v.AddMember("creditLimit", _creditLimit, allocator);

    v.AddMember("expMonth", _expiryDate.first, allocator);

    v.AddMember("expYear", _expiryDate.second, allocator);

    doc.PushBack(v, allocator);

    return true;
}

const std::shared_ptr<ClientCard> ClientCard::Deserialize(const rapidjson::Value& obj)
{
    std::shared_ptr<ClientCard> res = std::make_shared<ClientCard>(obj["number"].GetInt(),
                                                                   static_cast<ClientCard::CardType>(obj["type"].
                                                                       GetInt()),
                                                                   obj["name"].GetString(),
                                                                   obj["pin"].GetInt(),
                                                                   obj["balance"].GetInt64(),
                                                                   obj["expMonth"].GetInt(),
                                                                   obj["expYear"].GetInt());
    if (res->getType() == ClientCard::CardType::CREDIT)
        res->setCreditLimit(obj["creditLimit"].GetInt64());
    return res;
}

bool ClientCard::isExpired() const
{
    time_t theTime = time(NULL);
    struct tm* aTime = localtime(&theTime);

    int month = 1 + aTime->tm_mon;
    int year = aTime->tm_year + 1900;
    if (_expiryDate.second < year || (_expiryDate.second == year && _expiryDate.first < month))
        return true;
    return false;
}
