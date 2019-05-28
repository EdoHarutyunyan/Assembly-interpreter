#pragma once

#include "FileManager.h"
#include "Parser.h"
//#include "Type.h"

namespace compiler
{

class Compiler
{
public:
	Compiler(const std::string& file);
	~Compiler();

	void Start();
	ParsedFile getParsingResult() const;

private:
	filemanager::FileManager* m_fileManager;
	parser::Parser* m_parser;
};

}//namespace compiler
