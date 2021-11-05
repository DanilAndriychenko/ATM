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

	bool makeTransaction(Cards<ClientCard>& cards, Transaction::TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int reciever = 101);

	bool makeTransaction(Cards<ClientCard>& cards, const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& phone_number);

	void findTransactionsBySenderNumber(std::vector<Transaction>&);

	const std::shared_ptr<Transaction> findTransactionByID(const int64_t id);


private:
	Transactions(const std::string& filePath);
	Transactions(const Transactions&) = delete;
	void operator=(const Transactions&) = delete;
	std::string _filePath;

};