#pragma once
#include "User.h"
#include "../Utils/Utils.h"
#include <vector>

class Users : public JSONItem
{
public:
	Users(const std::string& filePath);
	virtual ~Users() {}

	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	const std::shared_ptr<User> findUserByID(const int64_t id);

	const std::vector<User>& getUsers() const { return _users; }

private:
	std::vector<User> _users;
	rapidjson::Document _doc;
};
