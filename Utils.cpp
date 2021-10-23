#include "Utils.h"
#include <regex>


const functionName Utilities::parseLine(const std::string& line, std::vector<functionArg>& tokenized)
{
	if (!tokenized.empty())
		tokenized.clear();
	const std::regex re("\\s+");
	std::sregex_token_iterator begin(line.begin(), line.end(), re, -1), end;
	std::copy(begin, end, std::back_inserter(tokenized));
	tokenized.erase(std::remove_if
					(tokenized.begin(),
					tokenized.end(),
					[](std::string const& s)
					{
						return s.size() == 0;
					}),
					tokenized.end());
	functionName fname = tokenized.at(0);
	tokenized.erase(tokenized.begin());
	return fname;
}