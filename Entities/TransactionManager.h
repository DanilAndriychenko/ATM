#pragma once
#include "Transaction.h"

class TransactionManager
{
public:
	static TransactionManager& getInstance()
	{
		static TransactionManager instance(TRANSACTIONS_PATH);
		return instance;
	}

	~TransactionManager() {}

	const std::shared_ptr<Transaction> makeTransaction(Transaction::TransactionType type, ClientCard* sender, const int64_t sum, const int receiver = 111);

	const std::shared_ptr<Transaction> makeTransaction(ClientCard* sender, const int64_t sum, const std::string& phone_number);

	void findTransactionsByClientNumber(std::vector<Transaction>& vec, const int numb);

	const std::shared_ptr<Transaction> findTransactionByID(const int64_t id);


private:
	TransactionManager(const std::string& filePath);
	TransactionManager(const TransactionManager&) = delete;
	void operator=(const TransactionManager&) = delete;
	std::string _filePath;
	rapidjson::Document _doc;
};