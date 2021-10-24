#pragma once
#include <string>

#include "..\rapidjson\rapidjson.h"
#include "..\rapidjson\document.h"		
#include "..\rapidjson\stringbuffer.h"	
#include "..\rapidjson\prettywriter.h"


class JSONItem
{
public:
//  bool DeserializeFromFile(const std::string& filePath);
	bool SerializeToFile(const std::string& filePath);
	virtual ~JSONItem() {}
	virtual std::string Serialize() const;
//	virtual bool Deserialize(const std::string& s);

//	virtual bool Deserialize(const rapidjson::Value& obj) = 0;
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const = 0;
};

bool InitDocument(const std::string& s, rapidjson::Document& doc);
