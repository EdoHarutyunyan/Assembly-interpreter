#pragma once

#include "ParsedFile.h"

namespace parser
{

using IsStackSize = std::tuple<bool, std::string>;
using IsDataSegment = std::tuple<bool, std::vector<std::string>>;
using IsCodeSegment = std::tuple<bool, std::vector<std::string>>;
using IsEntryPoint = std::tuple<bool, std::string>;
using FuncDefinitionMaps = std::vector<std::unordered_map<std::string, size_t>>;
using ParsedFiles = std::vector<ParsedFile>;
using Offsets = std::vector<size_t>;

class Parser
{
public:
	Parser() = default;
	~Parser() = default;

	void Start(const std::vector<std::string>& file);
		
	void StackSizeParser(const std::string& stackSizeSegment);
	void DataParser(const std::vector<std::string>& dataSegment);
	void CodeParser(const std::vector<std::string>& codeSegment);
	void EntryPointParser(const std::string& entryPointSegment);
		
	ParsedFiles GetParsedFiles() const;
		
private:
	void DevideIntoParts(const std::vector<std::string>& file,
		IsStackSize& stackSize, IsDataSegment& dataSegment,
		IsCodeSegment& codeSegment, IsEntryPoint& entryPoint);
	void WriteDataToDataStorage(const std::vector<std::string>& tokens);
	size_t DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& numInitList);
		
private:
	Offsets m_offsets;
	ParsedFiles m_parsedFiles;
	FuncDefinitionMaps m_funcDefinitionMaps;
	static size_t m_indexOfParsingFile;
};

void split(const std::string& line, std::vector<std::string>& res);
std::vector<std::string> InitialValueSplit(const std::string& line);

} // namespace parser