#pragma once

#include <algorithm>
#include <string>
#include <vector>


namespace utils
{
	using Args = std::vector<std::string>;
	using functionName = std::string;
	using functionArg = std::string;

	const functionName parseLine(const std::string&, std::vector<functionArg>&);

    bool is_double(const std::string& s);
    bool is_int(const std::string& s);

	unsigned hashStr(const char* s);

	void toLowerCase(std::string& str);
}