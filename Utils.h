#pragma once
#include <string>
#include <vector>

using functionArg = std::string;
using functionName = std::string;

namespace Utilities
{
	const functionName parseLine(const std::string&, std::vector<functionArg>&);
}