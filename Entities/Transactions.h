#pragma once
#include "Transaction.h"

class Transactions
{
public:
	static Transactions& getInstance()
	{
		static Transactions instance(TRANSACTIONS_PATH);
		return instance;
	}

	~Transactions() {}

	const std::shared_ptr<Transaction> makeTransaction(Transaction::TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int receiver = 111);

	const std::shared_ptr<Transaction> makeTransaction(const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& phone_number);

	void findTransactionsByClientNumber(std::vector<Transaction>& vec, const int numb);

	const std::shared_ptr<Transaction> findTransactionByID(const int64_t id);


private:
	Transactions(const std::string& filePath);
	Transactions(const Transactions&) = delete;
	void operator=(const Transactions&) = delete;
	std::string _filePath;
	rapidjson::Document _doc;
};