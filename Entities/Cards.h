#pragma once
#include "JSONItem.h"
#include <vector>

template <class T>
class Cards
{
	using deserializationFunct = const std::shared_ptr<T>(*)(const rapidjson::Value&);
public:

	Cards(const std::string& filePath, deserializationFunct funct);
	
	~Cards() {}

	const std::shared_ptr<T> findCardByNumber(const int numb);

	void findAllCards(std::vector<T>&) const;

	bool modifyCardData(const T& modified);

private:
	
	Cards(Cards const&) = delete;              // Don't Implement
	void operator=(Cards const&) = delete; // Don't implement

	rapidjson::Document _doc;
	void writeDocument() const;
	std::string _filePath;
	deserializationFunct _deserialize;
};

////////class implementation////////
template<class T>
Cards<T>::Cards(const std::string& filePath, deserializationFunct funct) : _filePath(filePath), _deserialize(funct), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

template <class T>
void Cards<T>::findAllCards(std::vector<T>& vec) const
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		vec.push_back(*(_deserialize(*itr).get()));
	}
}

template <class T>
const std::shared_ptr<T> Cards<T>::findCardByNumber(const int numb)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["number"].GetInt() == numb)
			return _deserialize(*itr);
	}
	return std::shared_ptr<T>(nullptr);
}

template <class T>
bool Cards<T>::modifyCardData(const T& modified)
{

	for (int idx = 0; idx < (int)_doc.Size(); idx++)
	{
		if (_doc[idx]["number"].GetInt() == modified.getNumber())
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
void Cards<T>::writeDocument() const
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