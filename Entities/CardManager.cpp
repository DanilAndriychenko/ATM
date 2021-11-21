#include "CardManager.h"

AbstractCardManager::~AbstractCardManager() {}

ClientCardManager::ClientCardManager() : _cards(new TemplateCardManager<ClientCard>(CLIENTS_DB_PATH)) {}

AdminCardManager::AdminCardManager() : _cards(new TemplateCardManager<AdminCard>(ADMINS_DB_PATH)) {}

ClientCardManager::~ClientCardManager()
{
	delete _cards;
}

const std::shared_ptr<ClientCard> ClientCardManager::findCardByNumber(const int numb)
{
	return _cards->findCardByNumber(numb);
}

void ClientCardManager::findAllCards(std::vector<ClientCard>& vec) const
{
	return _cards->findAllCards(vec);
}

bool ClientCardManager::modifyCardData(const ClientCard& modified)
{
	return _cards->modifyCardData(modified);
}


const std::shared_ptr<AdminCard> AdminCardManager::findCardByNumber(const int numb)
{
	return _cards->findCardByNumber(numb);
}

void AdminCardManager::findAllCards(std::vector<AdminCard>& vec) const
{
	return _cards->findAllCards(vec);
}

bool AdminCardManager::modifyCardData(const AdminCard& modified)
{
	return _cards->modifyCardData(modified);
}

AdminCardManager::~AdminCardManager()
{
	delete _cards;
}
