#include "Cards.h"

AbstractCards::~AbstractCards() {}

ClientCards::ClientCards() : _cards(new Cards<ClientCard>(CLIENTS_DB_PATH)) {}

AdminCards::AdminCards() : _cards(new AbstractCards::Cards<AdminCard>(ADMINS_DB_PATH)) {}

ClientCards::~ClientCards()
{
	delete _cards;
}

const std::shared_ptr<ClientCard> ClientCards::findCardByNumber(const int numb)
{
	return _cards->findCardByNumber(numb);
}

void ClientCards::findAllCards(std::vector<ClientCard>& vec) const
{
	return _cards->findAllCards(vec);
}

bool ClientCards::modifyCardData(const ClientCard& modified)
{
	return _cards->modifyCardData(modified);
}


const std::shared_ptr<AdminCard> AdminCards::findCardByNumber(const int numb)
{
	return _cards->findCardByNumber(numb);
}

void AdminCards::findAllCards(std::vector<AdminCard>& vec) const
{
	return _cards->findAllCards(vec);
}

bool AdminCards::modifyCardData(const AdminCard& modified)
{
	return _cards->modifyCardData(modified);
}

AdminCards::~AdminCards()
{
	delete _cards;
}
