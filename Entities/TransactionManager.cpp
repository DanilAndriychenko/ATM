#include "TransactionManager.h"


TransactionManager::TransactionManager(const std::string& filePath) : _filePath(filePath), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

const std::shared_ptr<Transaction> TransactionManager::makeTransaction(Transaction::TransactionType type, ClientCard* sender, const int64_t sum, const int receiver)
{
	std::shared_ptr<Transaction> ptr = std::make_shared<Transaction>(type,
																	sender,
																	sum,
																	receiver);
	ptr->doSerialize(_doc);
	writeDocument(_doc, _filePath);
	return ptr;
}

const std::shared_ptr<Transaction> TransactionManager::makeTransaction(ClientCard* sender, const int64_t sum, const std::string& phone_number)
{
	std::shared_ptr<Transaction> ptr = std::make_shared<Transaction>(Transaction::TransactionType::PHONE_TRANSFER, 
																	sender, 
																	sum,
																	phone_number);
	ptr->doSerialize(_doc);
	writeDocument(_doc, _filePath);
	return ptr;
}

void TransactionManager::findTransactionsByClientNumber(std::vector<Transaction>& vec, const int numb)
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["client_number"].GetInt() == numb)
			vec.push_back(*(Transaction::Deserialize(*itr)));
	}
}

const std::shared_ptr<Transaction> TransactionManager::findTransactionByID(const int64_t id)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt() == id)
			return Transaction::Deserialize(*itr);
	}
	return std::shared_ptr<Transaction>(nullptr);
}