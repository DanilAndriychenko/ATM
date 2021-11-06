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
	virtual ~JSONItem() {}
	bool doSerialize(rapidjson::Document& doc) const { return Serialize(doc); }
private:
	virtual bool Serialize(rapidjson::Document&) const = 0;
};

void InitDocument(const std::string&, rapidjson::Document&);

void writeDocument(const rapidjson::Document& doc, const std::string& filePath);