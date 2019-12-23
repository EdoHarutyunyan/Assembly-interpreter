#include "ParsedFile.h"
#include <string>
#include <sstream>

namespace parsedfile
{

SymbolTables symbol_tables;
UnresolvedSymbolTables unresolvedSymbols;

std::map<std::string, size_t> type_map = {
	{ "CHAR", 0 },
	{ "BYTE", 1 },
	{ "WORD", 2 },
	{ "DWORD", 3 },
	{ "QWORD", 4 }
};

std::ostream& operator<<(std::ostream& os, const ParsedFile& pf)
{
	os << pf.m_entryPoint;
	for (size_t i = 0; i < pf.m_dataStorage.size(); ++i)
	{
		os << pf.m_dataStorage[i];
	}
	for (size_t i = 0; i < pf.m_instruction.size(); ++i)
	{
		os << pf.m_instruction[i];
	}
	os << pf.m_entryPoint;

	return os;
}

std::istream& operator>>(std::istream& is, ParsedFile& pf)
{
	is >> pf.m_entryPoint;
	for (size_t i = 0; i < pf.m_dataStorage.size(); ++i)
	{
		is >> pf.m_dataStorage[i];
	}
	for (size_t i = 0; i < pf.m_instruction.size(); ++i)
	{
		is >> pf.m_instruction[i];
	}
	is >> pf.m_entryPoint;

	return is;
}

void UpdateDataInSymbolsTable(const std::string& identifier, const int offset, const size_t tableNumber)
{
	static uint16_t makeUnique = 1u;

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

	
	if (offset == -1)
	{
		symbol_tables[tableNumber].insert({ identifier, std::make_tuple(makeUnique*offset, false) });
		++makeUnique;
	}
	else
	{
		symbol_tables[tableNumber].insert({ identifier, std::make_tuple(offset, false) });
	}
}

void UpdateFuncInSymbolsTable(const std::string& identifier, const int offset, const size_t tableNumber)
{
	static uint16_t makeUnique = 100u;

	if (offset == -1)
	{
		symbol_tables[tableNumber].insert({ identifier, std::make_tuple(makeUnique * offset, true) });
		++makeUnique;
	}
	else
	{
		symbol_tables[tableNumber].insert({ identifier, std::make_tuple(offset, true) });
	}
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