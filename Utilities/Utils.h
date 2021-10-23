#pragma once

#include <string>
#include <vector>


namespace utils
{
	using Args = std::vector<std::string>;
	using functionName = std::string;

	const functionName parseLine(const std::string&, Args&);

	template<class T>
	T* strTo(const std::string&);

	template<int>
	int* strTo(const std::string& string)
	{
		stoi(string);
	}

	unsigned hashStr(const char* s);
}