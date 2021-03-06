#include "Compiler.h"
#include <iostream>

namespace compiler
{
using namespace parsedfile;

Compiler::Compiler(std::vector<std::string>&& paths)
	: m_linker(nullptr)
	, m_parser(std::make_shared<parser::Parser>(paths.size()))
	, m_fileManager(std::make_unique<filemanager::FileManager>(std::forward<std::vector<std::string>>(paths)))
{
}

void Compiler::Start()
{
	const auto paths = std::forward<std::vector<std::string>>(m_fileManager->GetPaths());
	
	for (const auto& path : paths)
	{
		m_parser->Start(m_fileManager->ReadFromFile(path));
	}
	
	m_linker = std::make_unique<linker::Linker>(std::move<std::weak_ptr<parser::Parser>>(m_parser));
	ParsedFile parsedFile = std::forward<ParsedFile>(m_linker->ToLink());
	m_fileManager->ToBynary(parsedFile);
}

std::string Compiler::GetBynaryFilePath() const
{
	return m_fileManager->GetBynaryFilePath();
}

} // namespace compiler
