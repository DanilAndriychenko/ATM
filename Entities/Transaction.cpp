#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <time.h>
#include <cmath>


//2.5%
const double Transaction::commision(0.025);
const int Transaction::bankID(555);

int64_t Transaction::hasher()
{
	return ((_date_time._secs * 37 ) ^ _date_time._minutes) ^ (_date_time._day * _date_time._month * _date_time._year);
}

bool Transaction::checkBalance(int diff)
{
	return (_type == Transaction::TransactionType::CASH_IN) || (_sender->getBalance() - _sum - diff >= (_sender->getType() == ClientCard::CardType::DEBIT ? 0 : -(_sender->getCreditLimit())));
}

void Transaction::initTransaction()
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	_date_time._year = aTime->tm_year + 1900;
	_date_time._month = aTime->tm_mon + 1;
	_date_time._day = aTime->tm_mday;
	_date_time._hours = aTime->tm_hour;
	_date_time._minutes = aTime->tm_min;
	_date_time._secs = aTime->tm_sec;
	_id = hasher();
	if (_sender->getNumber() == _receiver)
	{
		_isSuccessfull = false;
		_errorMsg = "Sender cannot be receiver simultaneously";
		return;
	}

	if (bankID == _sender->getNumber() % 1000 || _type == TransactionType::CHARITY_TRANSFER)
		_currentComission = 0.0;
	if (_type == TransactionType::PHONE_TRANSFER)
		_currentComission = commision + 0.01;
	//consider rounding
	int diff = round(_sum * _currentComission);
	
	if (!checkBalance(diff))
	{
		_isSuccessfull = false;
		_errorMsg = "Insufficient funds for transfer";
		return;
	}

	ClientCards& cards = ClientCards::getInstance();

	if (_type == TransactionType::CARD_TRANSFER)
	{
		std::shared_ptr<ClientCard> reciev_ptr = cards.findCardByNumber(_receiver);
		if (reciev_ptr.get() == nullptr)
		{
			_isSuccessfull = false;
			_errorMsg = "Reciever doesn`t exist";
			return;
		}
		reciev_ptr->setBalance(reciev_ptr->getBalance() + _sum);
		cards.modifyCardData(*reciev_ptr);
	}
	//I assume that phone number has been checked before
	if(_type != TransactionType::CASH_IN)
		_sender->setBalance(_sender->getBalance() - _sum - diff);
	else 
		_sender->setBalance(_sender->getBalance() + _sum - diff);
	cards.modifyCardData(*_sender);
}

Transaction::Transaction(TransactionType type, ClientCard* sender, const int64_t sum, const int reciever) :
	_type(type),
	_sender(sender),
	_receiver(reciever),
	_phone_number(""),
	_date_time(),
	_sum(sum),
	_isSuccessfull(true),
	_currentComission(commision),
	_errorMsg(""),
	_sender_number(sender->getNumber()),
	_sender_name(sender->getName()),
	_id(0)
{
	initTransaction();
}

Transaction::Transaction(TransactionType type, ClientCard* sender, const int64_t sum, const std::string& ph_numb) :
	_type(type),
	_sender(sender),
	_receiver(-1),
	_phone_number(ph_numb),
	_date_time(),
	_sum(sum),
	_isSuccessfull(true),
	_currentComission(commision),
	_errorMsg(""),
	_sender_number(sender->getNumber()),
	_sender_name(sender->getName()),
	_id(0)
{
	initTransaction();
}

Transaction::Transaction(TransactionType type, bool success, const std::string& errorMsg, const int sender_numb, const std::string& sender_name,
	const int receiver_numb, const std::string& receiver_phone, const int64_t sum,
	const int year, const int month, const int day, const int hours, const int mins, const int secs) :
	_type(type),
	_isSuccessfull(success),
	_sender_number(sender_numb),
	_sender_name(sender_name),
	_receiver(receiver_numb),
	_phone_number(receiver_phone),
	_currentComission(commision),
	_sum(sum),
	_date_time(year, month, day, hours, mins, secs),
	_errorMsg(errorMsg),
	_id(0)
{
	_id = hasher();
	if (bankID == _sender_number % 1000 || _type == TransactionType::CHARITY_TRANSFER)
		_currentComission = 0.0;
	if (_type == TransactionType::PHONE_TRANSFER)
		_currentComission = commision + 0.01;
}


bool Transaction::Serialize(rapidjson::Document& doc) const
{
	auto& allocator = doc.GetAllocator();

	rapidjson::Value v;

	v.SetObject();

	v.AddMember("id", _id, allocator);

	v.AddMember("success", _isSuccessfull, allocator);

	v.AddMember("type", static_cast<int>(_type), allocator);

	v.AddMember("client_number", _sender->getNumber(), allocator);

	v.AddMember("client_name", rapidjson::Value(_sender_name.c_str(), allocator).Move(), allocator);

	if(_type == TransactionType::CARD_TRANSFER)
		v.AddMember("receiver_number", _receiver, allocator);
	else if(_type == TransactionType::PHONE_TRANSFER)
		v.AddMember("receiver_phone", rapidjson::Value(_phone_number.c_str(), allocator).Move(), allocator);
	if(!_isSuccessfull)
		v.AddMember("errorMsg", rapidjson::Value(_errorMsg.c_str(), allocator).Move(), allocator);
	
	v.AddMember("sum", _sum, allocator);

	v.AddMember("year", _date_time._year, allocator);

	v.AddMember("month", _date_time._month, allocator);

	v.AddMember("day", _date_time._day, allocator);

	v.AddMember("hours", _date_time._hours, allocator);

	v.AddMember("minutes", _date_time._minutes, allocator);

	v.AddMember("seconds", _date_time._secs, allocator);

	doc.PushBack(v, allocator);

	return true;
}

const std::shared_ptr<Transaction> Transaction::Deserialize(const rapidjson::Value& obj)
{
	Transaction::TransactionType type = static_cast<Transaction::TransactionType>(obj["type"].GetInt());
	bool succ = obj["success"].GetBool();
	return std::make_shared<Transaction>(type,
											succ,
											succ ? "" : obj["errorMsg"].GetString(),
											obj["client_number"].GetInt(),
											obj["client_name"].GetString(),
											(type == Transaction::TransactionType::CARD_TRANSFER) ? obj["receiver_number"].GetInt() : -1,
											type == Transaction::TransactionType::PHONE_TRANSFER ? obj["receiver_phone"].GetString() : "",
											obj["sum"].GetInt64(),
											obj["year"].GetInt(),
											obj["month"].GetInt(),
											obj["day"].GetInt(),
											obj["hours"].GetInt(),
											obj["minutes"].GetInt(),
											obj["seconds"].GetInt());
}


std::ostream& Transaction::print(std::ostream& os) const
{
	os <<"-------------------------------TRANSACTION INFO-------------------------------\n";
	os << "| Client card number: " << _sender_number << '\n';
	os << "| Client name: " << _sender_name << '\n';
	switch (_type)
	{
	case TransactionType::PHONE_TRANSFER:
		os << "| Receiver phone number: " << _phone_number << '\n';
		break;
	case TransactionType::CARD_TRANSFER:
		os << "| Receiver card number: " << _receiver << '\n';
		break;
	case TransactionType::CHARITY_TRANSFER:
		os << "| Charity donation \n";
		break;
	case TransactionType::CASH_IN:
		os << "| Cash accrual \n";
		break;
	default :
		os << "| Cash withrawal\n";
	}
	os << "| Transfer sum: " << _sum << '\n';
	os << "| Comission: " << _currentComission * 100 << '%' << '\n';
	os << "| Date: " << _date_time._day << '.' << _date_time._month << '.' << _date_time._year << '\n';
	os << "| Time: "  << (_date_time._hours < 10 ? '0' : '\0') << _date_time._hours << ':' << (_date_time._minutes < 10 ? '0' : '\0') << _date_time._minutes
		<< ':' << (_date_time._secs < 10 ? '0' : '\0') << _date_time._secs << '\n';
	os << "| Status: " << (_isSuccessfull ? "Success" : ("Failed [" + _errorMsg + ']')) << '\n';
	os << "------------------------------------------------------------------------------\n";
	return os;
}