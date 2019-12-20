#pragma once
#include "Parser.h"
#include <iostream>

namespace linker
{
using ParserPtr = std::weak_ptr<parser::Parser>;

class Linker
{
public:
	Linker(ParserPtr&& parser);
	~Linker() = default;

	parsedfile::ParsedFile ToLink();
	std::unordered_map<std::string, size_t> ToLinkSymbolTables();

private:
	ParserPtr m_parser;
};

} // namespace linker


