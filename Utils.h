#pragma once

#include <string>
#include <vector>


namespace utils
{
	using Args = std::vector<std::string>;
	
	std::pair<std::string, Args> parseLine(const std::string&);

	unsigned hashStr(const char* s);
}