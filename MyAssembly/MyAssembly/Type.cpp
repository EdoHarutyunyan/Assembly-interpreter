#include "Type.h"

#include <string>
#include <sstream>

namespace type
{

std::unordered_map<std::string, size_t> type_table;

std::map<std::string, size_t> type_map = {
	{ "CHAR", 0 },
	{ "BYTE", 1 },
	{ "WORD", 2 },
	{ "DWORD", 3 },
	{ "QWORD", 4 }
};

void UpdateTypeTable(const std::string& identifier, const size_t offset)
{
	std::stringstream ss;
	char firstSimbol;
	size_t secondSimbol;

	ss << identifier;
	ss >> firstSimbol;

	// check if the name of the variable which was defined in data part 
	// is the same as the name one  of the registres it will throw an exception
	if (firstSimbol == 'A')
	{
		ss >> secondSimbol;

		if (ss.eof())
		{
			if (secondSimbol >= 0 && secondSimbol <= 7)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	ss.clear();

	if (firstSimbol == 'R')
	{
		ss >> secondSimbol;
		if (ss.eof())
		{
			if (secondSimbol >= 0 && secondSimbol <= 7)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	type_table[identifier] = offset;
}

Type to_enum(const size_t t)
{
	return static_cast<Type>(t);
}

char to_char(const std::string& from)
{
	std::stringstream buff;
	char to;

	buff << from;
	buff >> to;

	return to;
}

}// namespace type
