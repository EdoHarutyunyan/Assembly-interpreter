#pragma once
#include "../src/decl.h"
#include "Code.h"

#include <vector>
#include <unordered_map>
#include <map>

namespace parsedfile
{

using SymbolTables = std::vector<std::unordered_map<std::string, std::tuple<int16_t, bool>>>;
using UnresolvedSymbolTables = std::vector<std::map<std::string, int16_t>>;

class ParsedFile
{
public:
	ParsedFile()
		: m_stackSize(-1)
		, m_dataStorage(1024)
		, m_entryPoint(-1)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const ParsedFile& pf);
	friend std::istream& operator>>(std::istream& is, ParsedFile& pf);

public:
	int m_stackSize;
	std::vector<byte> m_dataStorage;
	std::vector<code::Code> m_instruction;
	int m_entryPoint;
};

enum Type
{
	CHAR = 0,
	BYTE = 1,
	WORD = 2,
	DWORD = 3,
	QWORD = 4
};

extern SymbolTables symbol_tables;

extern std::map<std::string, size_t> type_map;

extern UnresolvedSymbolTables unresolvedSymbols;

void UpdateDataInSymbolsTable(const std::string& identifier, int offset, size_t tableNumber);
void UpdateFuncInSymbolsTable(const std::string& identifier, int offset, size_t tableNumber);

Type to_enum(const size_t t);

} // namespace parsedFile 