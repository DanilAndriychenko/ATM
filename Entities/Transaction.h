#pragma once

//#include "JSONItem.h"
#include "ClientCard.h"
#include "Cards.h"

class Transaction final : public JSONItem
{
	friend class Transactions;
public:

	enum class TransactionType
	{
		CARD_TRANSFER = 0,
		PHONE_TRANSFER = 1,
		CHARITY_TRANSFER = 2,
	};

	struct DateTime
	{
		DateTime(const int year=0, const int month=0, const int day=0, const int hours=0, const int minutes=0, const int secs=0) :
			_year(year),
			_month(month),
			_day(day),
			_hours(hours),
			_minutes(minutes),
			_secs(secs)
		{}

		~DateTime() {}

		int _year;
		int _month;
		int _day;
		int _hours;
		int _minutes;
		int _secs;
	};

	
	//101 is charity number
	//Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int reciever=101);

	//Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& ph_numb);

	//for deserialization purposes only
	Transaction(TransactionType type, bool success, const std::string& errorMsg, const int sender_numb, const std::string& sender_name,
		const int receiver_numb, const std::string& receiver_phone, const int64_t sum,
		const int year, const int month, const int day, const int hours, const int mins, const int secs);


	~Transaction() {}
	
	static const std::shared_ptr<Transaction> Deserialize(const rapidjson::Value& obj);

	const std::shared_ptr<ClientCard>& getSender() const { return _sender; }
	const DateTime& getDate() const { return _date_time; }
	double getCommision() const { return commision; }
	int64_t getSum() const { return _sum; }
	bool isSuccessfull() const { return _isSuccessfull; }
	int64_t getID() const { return _id; }
	int64_t getReciever() const { return _receiver; }
	const std::string& getErrorMessage() const { return _errorMsg; }

	std::ostream& print(std::ostream& os) const;

private:
	Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int reciever = 101);
	Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& ph_numb);
	Transaction(const Transaction&) = delete;
	Transaction& operator=(const Transaction&) = delete;
	const TransactionType _type;
	DateTime _date_time;
	int64_t _sum;
	std::shared_ptr<ClientCard> _sender;
	const int _receiver;
	const std::string _phone_number;
	static int64_t freeID;
	const static double commision;
	//stands for 3 last digits of card number
	const static int bankID;
	const int64_t _id;
	double _currentComission;
	bool _isSuccessfull;
	std::string _errorMsg;
	bool checkBalance(int diff);
	void initTransaction(Cards<ClientCard>&);
	bool Serialize(rapidjson::Document&) const override;

	//for deserialization purposes
	const int _sender_number;
	const std::string _sender_name;
};

