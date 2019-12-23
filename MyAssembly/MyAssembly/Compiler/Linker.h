#pragma once
#include "Parser.h"
#include <iostream>

namespace linker
{
using ParserPtr = std::weak_ptr<parser::Parser>;
using Symbols = std::unordered_map<std::string, int16_t>;

class Linker
{
public:
	Linker(ParserPtr&& parser);
	~Linker() = default;

	parsedfile::ParsedFile ToLink();

private:
	ParserPtr m_parser;
};

} // namespace linker


