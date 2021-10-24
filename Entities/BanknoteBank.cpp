#include "BanknoteBank.h"

BanknoteBank::BanknoteBank() : _availableBanknotes()
{}

bool BanknoteBank::Deserialize(const rapidjson::Value& obj)
{
	for (int i = 0; i < obj.GetArray().Size(); i += 2)
	{
		_availableBanknotes.emplace(obj.GetArray()[i].GetInt(), obj.GetArray()[i + 1].GetInt());
	}
	return true;
}

bool BanknoteBank::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();
	for (std::pair<Banknote, int> p : _availableBanknotes)
	{
		writer->Int(p.first);
		writer->Int(p.second);
	}
	writer->EndArray();
	return true;
}
