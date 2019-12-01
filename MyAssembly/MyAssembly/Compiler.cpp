#include "Compiler.h"
#include "Interpreter.h"

#include <iostream>

namespace compiler
{

Compiler::Compiler(const std::string& file)
	: m_fileManager{new filemanager::FileManager(file)}
	, m_parser{new parser::Parser()}
{
}

Compiler::~Compiler()
{
	delete m_fileManager;
	delete m_parser;
}

void Compiler::Start()
{
	const std::string fileName = m_fileManager->GetFileName();
	m_parser->Start(m_fileManager->ReadFromFile(fileName));

	m_fileManager->ToBynary(m_parser->GetResult());
}

std::vector<std::string> Compiler::GetBynaryFile() const
{
	const std::string bynaryFileName = m_fileManager->GetBynaryFileName();
	return m_fileManager->ReadFromFile(bynaryFileName);
}

}//namespace compiler
