#include "Utils.h"

#include <regex>

const utils::functionName utils::parseLine(const std::string& line, Args& tokenized)
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

unsigned utils::hashStr(const char* s)
{
    unsigned h = 37;
    while (*s)
    {
        h = (h * 54059) ^ (s[0] * 76963);
        s++;
    }
    return h % 86969;
}

bool utils::is_double(const std::string& s)
{
    return std::regex_match(s, std::regex("[-+][\\d]+|[-+]\\d*\\.\\d+"));
}

bool utils::is_int(const std::string& s)
{
    return std::regex_match(s, std::regex("[-+]?[\\d]+"));
}

void utils::toLowerCase(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}
