#include "Utils.h"
#include <regex>

#include "../States/Authorization.h"

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

bool utils::matchPhoneNumber(const std::string& str)
{
	const std::regex re("\\+\\d?\\d?\\d{11}");
	return std::regex_match(str, re);
}

void utils::printBanknotes(int nominal, int quant)
{
	if(quant <= 0)
		return;
	std::string filePath = "Resources/" + std::to_string(nominal) + ".txt";
	std::ifstream f(filePath);
	if (f.is_open())
		std::cout << f.rdbuf();
	std::cout << "X " << quant << '\n';
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
	return std::regex_match(str, std::regex("[-]?[\\d]+"));
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



bool utils::isPassword(std::string& passwordString, int& res)
{
	if (utils::isInt(passwordString))
	{
		const int id = std::stoi(passwordString);
		const int numOfDigits = id / pow(10, Authorization::numOfDigitsInPassword - 1);
		if (numOfDigits > 0 && numOfDigits < 10)
		{
			res = id;
			return true;
		}
		std::cout << "Password must contain 4 digits\n";
		return false;
	}
	std::cout << "Password can contain only digits\n";
	return false;
}

bool utils::isID(std::string& idString, int& result)
{
    if (utils::isInt(idString))
    {
        const int id = std::stoi(idString);
        const int numOfDigits = id / pow(10, Authorization::numOfDigitsInLogin - 1);
        if (numOfDigits > 0 && numOfDigits < 10)
        {
            result = id;
            return true;
        }
        std::cout << "ID must contain" << Authorization::numOfDigitsInLogin << " digits\n";
        return false;
    }
    std::cout << "ID can contain only digits\n";
    return false;
}
