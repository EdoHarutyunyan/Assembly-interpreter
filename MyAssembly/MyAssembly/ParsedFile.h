#pragma once
#include "decl.h"
#include "Code.h"

#include <vector>
#include <unordered_map>
#include <map>

namespace parsedfile
{

using SymbolTables = std::vector<std::unordered_map<std::string, int>>;

class ParsedFile
{
public:
	ParsedFile()
		: m_stackSize(0u)
		, m_dataStorage(1024)
		, m_entryPoint(0u)
	{
	}

public:
	size_t m_stackSize;
	std::vector<byte> m_dataStorage;
	std::vector<code::Code> m_instruction;
	size_t m_entryPoint;
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

void UpdateSymbolsTable(const std::string& identifier, int offset, size_t tableNumber);

Type to_enum(const size_t t);

} // namespace parsedFile 