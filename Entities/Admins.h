#pragma once
#include "Admin.h"
#include "../Utilities/Utils.h"
#include <vector>

class Admins : public JSONItem
{
public:
	Admins(const std::string& filePath);
	virtual ~Admins() {}

	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	const std::shared_ptr<Admin> findAdminByID(const int64_t id);
	
	const std::vector<Admin>& getAdmins() const { return _admins; }

private:
	std::vector<Admin> _admins;
	rapidjson::Document _doc;
};

