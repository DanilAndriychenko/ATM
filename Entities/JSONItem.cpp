#include "JSONItem.h"

void InitDocument(const std::string& s, rapidjson::Document& doc)
{
	//if (s.empty())
	//	throw Exceptions::DeserializeException("Wrong file path!");

	std::string validJson(s);

	if (doc.Parse(validJson.c_str()).HasParseError())
		throw Exceptions::DeserializeException("Wrong file format!");
}


void writeDocument(const rapidjson::Document& doc, const std::string& filePath)
{
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	std::ofstream f(filePath);

	f << buffer.GetString();
	f.flush();
	f.close();
}