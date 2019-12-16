#pragma once
#include "Parser.h"
#include <iostream>

namespace linker
{
	using ParserPtr = std::shared_ptr<parser::Parser>;
class Linker
{
public:
	Linker(const ParserPtr& parser);
	~Linker() = default;

	ParsedFile ToLink();

private:
	ParserPtr m_parser;
};

} // namespace linker


