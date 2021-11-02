#include "JSONItem.h"

void InitDocument(const std::string& s, rapidjson::Document& doc)
{
	if (s.empty())
		throw Exceptions::DeserializeException("Wrong file path!");

	std::string validJson(s);

	if (doc.Parse(validJson.c_str()).HasParseError())
		throw Exceptions::DeserializeException("Wrong file format!");
}