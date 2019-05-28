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
	m_parser->Start(m_fileManager->ReadFromFile());
}

ParsedFile Compiler::getParsingResult() const
{
	return m_parser->getResult();
}

}//namespace compiler
