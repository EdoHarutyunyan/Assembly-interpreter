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

	ParsedFile ToLink();

private:
	ParserPtr m_parser;
};

} // namespace linker


