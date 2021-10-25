#include "BanknoteBank.h"

BanknoteBank::BanknoteBank(const std::string& filePath) : _availableBanknotes(), _doc()
{
	std::string bufferAdm = utils::getStringBuffer(filePath);
	InitDocument(bufferAdm, _doc);
	//if (!InitDocument(buffer, _doc))
	//		throw exception;
	//if(!_doc.isArray())
	//      throw exception;
	for (int i = 0; i < _doc.GetArray().Size(); i += 2)
	{
		_availableBanknotes.emplace(_doc.GetArray()[i].GetInt(), _doc.GetArray()[i + 1].GetInt());
	}
}

//std::shared_ptr<BanknoteBank> BanknoteBank::Deserialize(const rapidjson::Value& obj)
//{
//	for (int i = 0; i < obj.GetArray().Size(); i += 2)
//	{
//		_availableBanknotes.emplace(obj.GetArray()[i].GetInt(), obj.GetArray()[i + 1].GetInt());
//	}
//	return true;
//
//}

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
