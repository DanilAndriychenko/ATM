#include "Utils.h"

#include <regex>

std::pair<std::string, utils::Args> utils::parseLine(const std::string& line)
{
	const std::regex re("\\s+");
	std::sregex_token_iterator it{ line.begin(),line.end(), re, -1 };
	std::vector<std::string> tokenized{ it, {} };
	tokenized.erase(std::remove_if
					(tokenized.begin(), 
					tokenized.end(),
					[](std::string const& s) {
						return s.size() == 0;
					}),
	tokenized.end());
	std::string funcName = tokenized.at(0);
	tokenized.erase(tokenized.begin());
	return std::pair{funcName, tokenized};
}

unsigned utils::hashStr(const char* s)
{
	unsigned h = 37;
	while (*s) {
		h = (h * 54059) ^ (s[0] * 76963);
		s++;
	}
	return h % 86969;
}
