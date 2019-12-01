#pragma once

#include "FileManager.h"
#include "Parser.h"
//#include "Type.h"

namespace compiler
{

class Compiler
{
public:
	explicit Compiler(const std::string& file);
	~Compiler();

	void Start();

	void ParsedResultToBynaryFile();
	std::vector<std::string> GetBynaryFile() const;

private:
	filemanager::FileManager* m_fileManager;
	parser::Parser* m_parser;
};

}//namespace compiler
