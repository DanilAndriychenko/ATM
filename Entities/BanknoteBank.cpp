#include "BanknoteBank.h"

BanknoteBank::BanknoteBank(const std::string& filePath) : _availableBanknotes(), _doc(), _filePath(filePath)
{
	std::string bufferAdm = utils::getStringBuffer(filePath);
	InitDocument(bufferAdm, _doc);
	for (int i = 0; i < _doc.GetArray().Size(); i += 2)
	{
		_availableBanknotes.emplace(_doc.GetArray()[i].GetInt(), _doc.GetArray()[i + 1].GetInt());
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

