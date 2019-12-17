#pragma once
#include <iostream>
#include <vector>
#include "Parser.h"
#include "FileManager.h"
#include "Linker.h"

namespace compiler
{

using FileManagerPtr = std::unique_ptr<filemanager::FileManager>;
using ParserPtr = std::shared_ptr<parser::Parser>;
using LinkerPtr = std::unique_ptr<linker::Linker>;

class Compiler
{
public:
	explicit Compiler(std::vector<std::string>&& paths);
	~Compiler() = default;

	void Start();

	std::vector<std::string> GetBynaryFile() const;
private:
	FileManagerPtr m_fileManager;
	ParserPtr m_parser;
	LinkerPtr m_linker;
};

} // namespace compiler
