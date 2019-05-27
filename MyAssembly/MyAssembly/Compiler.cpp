#include "Compiler.h"
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

void Compiler::print()
{
	std::vector<byte> x = m_parser->getDataStorage();

	word* p = reinterpret_cast<word*>(&x[0]);
	std::cout << *p << std::endl;
}

}//namespace compiler
