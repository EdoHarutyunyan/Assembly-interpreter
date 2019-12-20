#include "ParsedFile.h"
#include <string>
#include <sstream>

namespace parsedfile
{

SymbolTables symbol_tables;

std::map<std::string, size_t> type_map = {
	{ "CHAR", 0 },
	{ "BYTE", 1 },
	{ "WORD", 2 },
	{ "DWORD", 3 },
	{ "QWORD", 4 }
};

void UpdateSymbolsTable(const std::string& identifier, const int offset, const size_t tableNumber)
{
	std::stringstream ss;
	char firstSimbol;
	size_t secondSymbol;

	ss << identifier;
	ss >> firstSimbol;

	// check if the name of the variable which was defined in data part 
	// is the same as the name one of the registres it will throw an exception
	if (firstSimbol == 'A')
	{
		ss >> secondSymbol;

		if (ss.eof())
		{
			if (secondSymbol >= 0 && secondSymbol <= 7)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	ss.clear();

	if (firstSimbol == 'R')
	{
		ss >> secondSymbol;
		if (ss.eof())
		{
			if (secondSymbol >= 0 && secondSymbol <= 63)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	symbol_tables[tableNumber][identifier] = offset;
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

} // namespace parsedFile