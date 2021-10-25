#include "Users.h"

Users::Users(const std::string& filePath) : _users(), _doc()
{
	std::string bufferUs = utils::getStringBuffer(filePath);
	InitDocument(bufferUs, _doc);
	//if (!InitDocument(buffer, _doc))
	//		throw exception;
	//if(!_doc.isArray())
	//      throw exception;
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		_users.push_back(*(User::Deserialize(*itr).get()));
	}
}

bool Users::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	for (std::vector<User>::const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		(*it).doSerialize(writer);
	}
	writer->EndArray();

	return true;
}

const std::shared_ptr<User> Users::findUserByID(const int64_t id)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt64() == id)
			return User::Deserialize(*itr);
	}
	return std::shared_ptr<User>(nullptr);
}