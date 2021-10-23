#include "Maintenance.h"
#include <functional>

std::unordered_map<std::string, void (Maintenance::*)(utils::Args)> _comsToPtrs
{
	{std::string(""), &Maintenance::test}
};

std::unordered_map<std::string, std::string> u = {
	{"RED","#FF0000"},
{"GREEN","#00FF00"},
{"BLUE","#0000FF"}
};