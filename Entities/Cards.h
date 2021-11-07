#pragma once
#include <vector>
#include "AdminCard.h"
#include "ClientCard.h"

class AbstractCards
{
public:
	virtual ~AbstractCards() = 0;
protected:
	template<class T>
	class Cards;
};


class ClientCards final : private AbstractCards
{
public:
	static ClientCards& getInstance()
	{
		static ClientCards instance;
		return instance;
	}

	~ClientCards() { delete _cards; }

	const std::shared_ptr<ClientCard> findCardByNumber(const int numb);

	void findAllCards(std::vector<ClientCard>&) const;

	bool modifyCardData(const ClientCard& modified);

	ClientCards(const ClientCards&) = delete;
	void operator=(const ClientCards&) = delete;

private:
	ClientCards();
	Cards<ClientCard>* _cards;
};

class AdminCards final : private AbstractCards
{
public:
	static AdminCards& getInstance()
	{
		static AdminCards instance;
		return instance;
	}

	~AdminCards() { delete _cards; }

	const std::shared_ptr<AdminCard> findCardByNumber(const int numb);

	void findAllCards(std::vector<AdminCard>&) const;

	bool modifyCardData(const AdminCard& modified);

	AdminCards(const AdminCards&) = delete;
	void operator=(const AdminCards&) = delete;

private:
	AdminCards();
	Cards<AdminCard>* _cards;
};



template <class T>
class AbstractCards::Cards
{
//	using deserializationFunct = const std::shared_ptr<T>(*)(const rapidjson::Value&);
public:
	
	Cards(const std::string& filePath);

	~Cards() {}

	const std::shared_ptr<T> findCardByNumber(const int numb);

	void findAllCards(std::vector<T>&) const;

	bool modifyCardData(const T& modified);

	Cards(Cards const&) = delete;              // Don't Implement
	void operator=(Cards const&) = delete; // Don't implement

private:

	rapidjson::Document _doc;
	std::string _filePath;
};


////////class implementation////////
template<class T>
AbstractCards::Cards<T>::Cards(const std::string& filePath) : _filePath(filePath), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

template <class T>
void AbstractCards::Cards<T>::findAllCards(std::vector<T>& vec) const
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		vec.push_back(*T::Deserialize(*itr));
		//vec.push_back(*(_deserialize(*itr).get()));
	}
}

template <class T>
const std::shared_ptr<T> AbstractCards::Cards<T>::findCardByNumber(const int numb)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["number"].GetInt() == numb)
			return T::Deserialize(*itr);
	}
	return std::shared_ptr<T>(nullptr);
}

template <class T>
bool AbstractCards::Cards<T>::modifyCardData(const T& modified)
{

	for (int idx = 0; idx < (int)_doc.Size(); idx++)
	{
		if (_doc[idx]["number"].GetInt() == modified.getNumber())
		{
			_doc.Erase(_doc.Begin() + idx--);
			
			modified.doSerialize(_doc);

			writeDocument(_doc, _filePath);
			return true;
		}
	}
	return false;
}


