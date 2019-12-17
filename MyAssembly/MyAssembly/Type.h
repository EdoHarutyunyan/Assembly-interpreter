#pragma once

#include <unordered_map>
#include <map>

namespace type
{

enum Type
{
	CHAR  = 0,
	BYTE  = 1,
	WORD  = 2,
	DWORD = 3,
	QWORD = 4
};

extern std::unordered_map<std::string, size_t> symbol_table;

extern std::map<std::string, size_t> type_map;

void UpdateSymbolsTable(const std::string& identifier, const size_t offset);

Type to_enum(const size_t t);

char to_char(const std::string& from);

}//namespace type
