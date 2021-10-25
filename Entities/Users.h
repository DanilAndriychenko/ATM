#pragma once
#include "User.h"
#include <vector>

class Users final : public JSONItem
{
public:
	Users(const std::string& filePath);
	~Users() {}

	const std::shared_ptr<User> findUserByID(const int64_t id);

	const std::vector<User>& getUsers() const { return _users; }

private:
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override;
	std::vector<User> _users;
	rapidjson::Document _doc;
};
