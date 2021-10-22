#include "Utils.h"
#include <regex>

std::pair<std::string, std::vector<functionArg>> Utilities::parseLine(const std::string& line)
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
	return std::pair<std::string, std::vector<functionArg>>{funcName, tokenized};
}