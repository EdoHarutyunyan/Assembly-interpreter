#include "Linker.h"

namespace linker
{

Linker::Linker(ParserPtr&& parser)
	: m_parser(std::forward<ParserPtr>(parser))
{
}

ParsedFile Linker::ToLink()
{
	if (auto weakPtr = m_parser.lock())
	{
		parser::ParsedFiles parsedFiles = std::forward<parser::ParsedFiles>(weakPtr->GetParsedFiles());
		// 2 checks
		// 2 merges
	}
	return{};
}

} // namespace linker