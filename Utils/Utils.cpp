#include "Utils.h"

#include <fstream>
#include <sstream>
#include <regex>

const CommandName utils::parseLine(const std::string& line, Args& tokenized)
{
	if (!tokenized.empty()) tokenized.clear();

	const std::regex re("\\s+");
	const std::sregex_token_iterator begin(line.begin(), line.end(), re, -1), end;
	std::copy(begin, end, std::back_inserter(tokenized));
	tokenized.erase(std::ranges::remove_if
					(tokenized,
					 [](std::string const& s)
					 {
						 return s.size() == 0;
					 }).begin(),
					tokenized.end());
	CommandName commandName = tokenized.at(0);
	tokenized.erase(tokenized.begin());
	return commandName;
}

unsigned utils::hashStr(const char* s)
{
	// TODO use constexpr for magic nums or maybe consider some another algorithm
	unsigned h = 37;
	while (*s)
	{
		h = (h * 54059) ^ (s[0] * 76963);
		s++;
	}
	return h % 86969;
}

bool utils::isDouble(const std::string& str)
{
	return std::regex_match(str, std::regex("[-+][\\d]+|[-+]\\d*\\.\\d+"));
}

bool utils::isInt(const std::string& str)
{
	return std::regex_match(str, std::regex("[-+]?[\\d]+"));
}

void utils::toLowerCase(std::string& str)
{
	std::ranges::transform(str, str.begin(),
						   [](const unsigned char c) -> int
						   {
							   return std::tolower(c);
						   });
}

const std::string utils::getStringBuffer(const std::string& filePath)
{
	std::ifstream f(filePath);
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return buffer.str();
}
