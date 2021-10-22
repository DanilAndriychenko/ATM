#pragma once
#include <string>
#include <vector>

using functionArg = std::string;

namespace Utilities
{
	std::pair<std::string, std::vector<functionArg>> parseLine(const std::string&);
}