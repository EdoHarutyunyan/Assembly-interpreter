#include "Linker.h"

namespace linker
{

Linker::Linker(const ParserPtr& parser)
	: m_parser(std::make_shared<parser::Parser>(parser))
{
}

ParsedFile Linker::ToLink()
{
	//m_parser.lock();
	parser::ParsedFiles parsedFiles = std::forward<std::vector<ParsedFile>>(m_parser->GetParsedFiles());
}

} // namespace linker