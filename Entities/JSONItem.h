#pragma once
#include <string>

#include "..\rapidjson\rapidjson.h"
#include "..\rapidjson\document.h"		
#include "..\rapidjson\stringbuffer.h"	
#include "..\rapidjson\prettywriter.h"

#include "../Utils/Utils.h"

class JSONItem
{
public:

	bool SerializeToFile(const std::string& filePath);
	virtual ~JSONItem() {}
	bool doSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const { return Serialize(writer); }
private:
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;
	virtual std::string Serialize() const;
};

bool InitDocument(const std::string& s, rapidjson::Document& doc);
