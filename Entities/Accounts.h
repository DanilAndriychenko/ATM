#pragma once
#include "JSONItem.h"
#include <vector>

template <class T>
class Accounts
{
public:
	Accounts(const std::string& filePath, const std::shared_ptr<T>(*deser)(const rapidjson::Value&));
	
	~Accounts() {}

	const std::shared_ptr<T> findAccountByID(const int64_t id);

	void findAllAccounts(std::vector<T>&) const;

	bool modifyAccount(const T& modified);

private:
	rapidjson::Document _doc;
	void writeDocument() const;
	std::string _filePath;
	const std::shared_ptr<T>(*_deserialize)(const rapidjson::Value&);
};

////////class implementation////////
template<class T>
Accounts<T>::Accounts(const std::string& filePath, const std::shared_ptr<T>(*fptr)(const rapidjson::Value&)) : _filePath(filePath), _deserialize(fptr), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

template <class T>
void Accounts<T>::findAllAccounts(std::vector<T>& vec) const
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		vec.push_back(*(_deserialize(*itr).get()));
	}
}

template <class T>
const std::shared_ptr<T> Accounts<T>::findAccountByID(const int64_t id)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt64() == id)
			return _deserialize(*itr);
	}
	return std::shared_ptr<T>(nullptr);
}

template <class T>
bool Accounts<T>::modifyAccount(const T& modified)
{

	for (int idx = 0; idx < (int)_doc.Size(); idx++)
	{
		if (_doc[idx]["id"].GetInt64() == modified.getID())
		{
			_doc.Erase(_doc.Begin() + idx--);
			
			modified.doSerialize(_doc);

			writeDocument();
			return true;
		}
	}
	return false;
}

template <class T>
void Accounts<T>::writeDocument() const
{
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	_doc.Accept(writer);

	std::ofstream f(_filePath);

	f << buffer.GetString();
	f.flush();
	f.close();
}