#include "Transactions.h"


Transactions::Transactions(const std::string& filePath) : _filePath(filePath), _doc()
{
	std::string buffer = utils::getStringBuffer(filePath);
	InitDocument(buffer, _doc);
	if (!_doc.IsArray())
		throw Exceptions::DeserializeException("Document is not an array!");
}

//add operation with banknote bank??!!!!!
const std::shared_ptr<Transaction> Transactions::makeTransaction(Cards<ClientCard>& cards, Transaction::TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int receiver)
{
	std::shared_ptr<Transaction> ptr = std::make_shared<Transaction>(cards,
																	type,
																	sender,
																	sum,
																	receiver);
	ptr->doSerialize(_doc);
	writeDocument(_doc, _filePath);
	return ptr;
}

const std::shared_ptr<Transaction> Transactions::makeTransaction(Cards<ClientCard>& cards, const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& phone_number)
{
	std::shared_ptr<Transaction> ptr = std::make_shared<Transaction>(cards, 
																	Transaction::TransactionType::PHONE_TRANSFER, 
																	sender, 
																	sum,
																	phone_number);
	ptr->doSerialize(_doc);
	writeDocument(_doc, _filePath);
	return ptr;
}

void Transactions::findTransactionsByClientNumber(std::vector<Transaction>& vec, const int numb)
{
	if (!vec.empty())
		vec.clear();
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["client_number"].GetInt() == numb)
			vec.push_back(*(Transaction::Deserialize(*itr)));
	}
}

const std::shared_ptr<Transaction> Transactions::findTransactionByID(const int64_t id)
{
	for (rapidjson::Value::ConstValueIterator itr = _doc.Begin(); itr != _doc.End(); ++itr)
	{
		if ((*itr)["id"].GetInt() == id)
			return Transaction::Deserialize(*itr);
	}
	return std::shared_ptr<Transaction>(nullptr);
}