#pragma once
#include <vector>
#include "AdminCard.h"
#include "ClientCard.h"

class AbstractCardManager
{
public:
	virtual ~AbstractCardManager() = 0;
protected:
	template<class T>
	class TemplateCardManager;
};


class ClientCardManager final : private AbstractCardManager
{
public:
	static ClientCardManager& getInstance()
	{
		static ClientCardManager instance;
		return instance;
	}

	~ClientCardManager();

	const std::shared_ptr<ClientCard> findCardByNumber(const int numb);

	void findAllCards(std::vector<ClientCard>&) const;

	bool modifyCardData(const ClientCard& modified);

	ClientCardManager(const ClientCardManager&) = delete;
	void operator=(const ClientCardManager&) = delete;

private:
	ClientCardManager();
	TemplateCardManager<ClientCard>* _cards;
};

class AdminCardManager final : private AbstractCardManager
{
public:
	static AdminCardManager& getInstance()
	{
		static AdminCardManager instance;
		return instance;
	}

	~AdminCardManager();

	const std::shared_ptr<AdminCard> findCardByNumber(const int numb);

	void findAllCards(std::vector<AdminCard>&) const;

	bool modifyCardData(const AdminCard& modified);

	AdminCardManager(const AdminCardManager&) = delete;
	void operator=(const AdminCardManager&) = delete;

private:
	AdminCardManager();
	TemplateCardManager<AdminCard>* _cards;
};


template <class T>
class AbstractCardManager::TemplateCardManager
{
public:
	
	TemplateCardManager(const std::string& filePath);

	~TemplateCardManager() {}

	const std::shared_ptr<T> findCardByNumber(const int numb);

	void findAllCards(std::vector<T>&) const;

	bool modifyCardData(const T& modified);

	TemplateCardManager(TemplateCardManager const&) = delete;              // Don't Implement
	void operator=(TemplateCardManager const&) = delete; // Don't implement

private:

	rapidjson::Document _doc;
	std::string _filePath;
};


////////class implementation////////
template<class T>
AbstractCardManager::TemplateCardManager<T>::TemplateCardManager(const std::string& filePath) : _filePath(filePath), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

template <class T>
void AbstractCardManager::TemplateCardManager<T>::findAllCards(std::vector<T>& vec) const
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		vec.push_back(*T::Deserialize(*itr));
	}
}

template <class T>
const std::shared_ptr<T> AbstractCardManager::TemplateCardManager<T>::findCardByNumber(const int numb)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["number"].GetInt() == numb)
			return T::Deserialize(*itr);
	}
	return std::shared_ptr<T>(nullptr);
}

template <class T>
bool AbstractCardManager::TemplateCardManager<T>::modifyCardData(const T& modified)
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