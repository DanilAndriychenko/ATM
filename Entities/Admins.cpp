#include "Admins.h"

Admins::Admins(const std::string& filePathAdm) : _admins(), _doc()
{
	std::string bufferAdm = utils::getStringBuffer(filePathAdm);
	InitDocument(bufferAdm, _doc);
	//if (!InitDocument(buffer, _doc))
	//		throw exception;
	//if(!_doc.isArray())
	//      throw exception;
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		_admins.push_back(*(Admin::Deserialize(*itr).get()));
	}
}

bool Admins::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	for (std::vector<Admin>::const_iterator it = _admins.begin(); it != _admins.end(); it++)
	{
		(*it).doSerialize(writer);
	}
	writer->EndArray();

	return true;
}

const std::shared_ptr<Admin> Admins::findAdminByID(const int64_t id)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt64() == id)
			return Admin::Deserialize(*itr);	
	}
	return std::shared_ptr<Admin>(nullptr);
}