#pragma once

#include <iostream>
#include <vector>

#include "Parser.h"
#include "FileManager.h"
#include "Linker.h"

namespace compiler
{

using LinkerPtr = std::unique_ptr<linker::Linker>;
using ParserPtr = std::shared_ptr<parser::Parser>;
using FileManagerPtr = std::unique_ptr<filemanager::FileManager>;

class Compiler
{
public:
	explicit Compiler(std::vector<std::string>&& paths);
	~Compiler() = default;

	void Start();

	std::string GetBynaryFilePath() const;

private:
	LinkerPtr m_linker;
	ParserPtr m_parser;
	FileManagerPtr m_fileManager;
};

} // namespace compiler
