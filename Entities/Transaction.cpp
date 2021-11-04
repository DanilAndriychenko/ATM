#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <time.h>
#include <cmath>

int64_t Transaction::freeID = 0;
//2.5%
const double Transaction::commision(0.025);
const int Transaction::bankID(555);

bool Transaction::checkBalance(int diff)
{
	//check whether debit or credit 
	if (_sender.get()->getBalance() - _sum - diff < (_sender->getType() == ClientCard::CardType::DEBIT ? 0 : -(_sender->getCreditLimit())))
		return false;
	return true;
}

void Transaction::initTransaction(Cards<ClientCard>& cards)
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	_date_time._year = aTime->tm_year + 1900;
	_date_time._month = aTime->tm_mon + 1;
	_date_time._day = aTime->tm_mday;
	_date_time._hours = aTime->tm_hour;
	_date_time._minutes = aTime->tm_min;
	_date_time._secs = aTime->tm_sec;

	if (_sender->getNumber() == _receiver)
	{
		_isSuccessfull = false;
		_errorMsg = "Sender cannot be receiver simultaneously";
		return;
	}

	if (bankID == _sender.get()->getNumber() % 1000 || _type == TransactionType::CHARITY_TRANSFER)
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
	if (_type == TransactionType::CARD_TRANSFER)
	{
		std::shared_ptr<ClientCard> reciev_ptr = cards.findCardByNumber(_receiver);
		if (reciev_ptr.get() == nullptr)
		{
			_isSuccessfull = false;
			_errorMsg = "Reciever doesn`t exist";
			return;
		}
		reciev_ptr->setBalance(reciev_ptr->getBalance() + _sum - _sum * _currentComission);
		cards.modifyCardData(*reciev_ptr);
	}
	//I assume that phone number has been checked before

	_sender->setBalance(_sender->getBalance() - _sum - diff);
	cards.modifyCardData(*_sender);
}

Transaction::Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const int reciever) :
	_type(type),
	_sender(sender),
	_receiver(reciever),
	_phone_number(""),
	_date_time(),
	_sum(sum),
	_isSuccessfull(true),
	_currentComission(commision),
	_errorMsg(""),
	_id(++freeID)
{
	initTransaction(cards);
}

Transaction::Transaction(Cards<ClientCard>& cards, TransactionType type, const std::shared_ptr<ClientCard> sender, const int64_t sum, const std::string& ph_numb) :
	_type(type),
	_sender(sender),
	_receiver(-1),
	_phone_number(ph_numb),
	_date_time(),
	_sum(sum),
	_isSuccessfull(true),
	_currentComission(commision),
	_errorMsg(""),
	_id(++freeID)
{
	initTransaction(cards);
}

bool Transaction::Serialize(rapidjson::Document& doc) const
{
	auto& allocator = doc.GetAllocator();

	rapidjson::Value v;

	v.SetObject();

	v.AddMember("id", _id, allocator);

	v.AddMember("success", _isSuccessfull, allocator);

	v.AddMember("type", static_cast<int>(_type), allocator);

	v.AddMember("sender_number", _sender->getNumber(), allocator);

	v.AddMember("reciever_number", _receiver, allocator);

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



std::ostream& Transaction::print(std::ostream& os) const
{
	os <<"-------------------------------TRANSACTION INFO-------------------------------\n";
	os << "| Sender card number: " << _sender->getNumber() << '\n';
	os << "| Sender name: " << _sender->getName() << '\n';
	if (_type == TransactionType::PHONE_TRANSFER)
		os << "| Receiver phone number: " << _phone_number << '\n';
	else if (_type == TransactionType::CARD_TRANSFER)
		os << "| Receiver card number: " << _receiver << '\n';
	else
		os << "| Charity donation \n";
	os << "| Transfer sum: " << _sum << '\n';
	os << "| Comission: " << _currentComission * 100 << '%' << '\n';
	os << "| Date: " << _date_time._day << '.' << _date_time._month << '.' << _date_time._year << '\n';
	os << "| Time: "  << (_date_time._hours < 10 ? '0' : '\0') << _date_time._hours << ':' << (_date_time._minutes < 10 ? '0' : '\0') << _date_time._minutes
		<< ':' << (_date_time._secs < 10 ? '0' : '\0') << _date_time._secs << '\n';
	os << "| Status: " << (_isSuccessfull ? "Success" : ("Failed [" + _errorMsg + ']')) << '\n';
	os << "------------------------------------------------------------------------------\n";
	return os;
}