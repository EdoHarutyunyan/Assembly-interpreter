#pragma once

#include "ParsedFile.h"

namespace parser
{
	
using IsStackSize = std::tuple<bool, std::string>;
using IsDataSegment = std::tuple<bool, std::vector<std::string>>;
using IsCodeSegment = std::tuple<bool, std::vector<std::string>>;
using IsEntryPoint = std::tuple<bool, std::string>;
using ParsedFiles = std::vector<parsedfile::ParsedFile>;
using Offsets = std::vector<size_t>;
using Labels = std::vector<std::map<std::string /*labelName*/, int8_t /*index*/>>;

class Parser
{
public:
	explicit Parser(const size_t& parsingFilesCount);
	~Parser() = default;

	void Start(const std::vector<std::string>& file);
		
	void StackSizeParser(const std::string& stackSizeSegment);
	void DataParser(const std::vector<std::string>& dataSegment);
	void CodeParser(const std::vector<std::string>& codeSegment);
	void EntryPointParser(const std::string& entryPointSegment);
		
	ParsedFiles GetParsedFiles() const;
	Labels GetLabels() const;
		
private:
	void DevideIntoParts(const std::vector<std::string>& file,
		IsStackSize& stackSize, IsDataSegment& dataSegment,
		IsCodeSegment& codeSegment, IsEntryPoint& entryPoint);
	void WriteDataToDataStorage(std::vector<std::string>&& tokens);
	size_t DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& numInitList);
		
private:
	Offsets m_offsets;
	ParsedFiles m_parsedFiles;
	Labels m_labels;
	size_t m_indexOfParsingFile;
};

void split(const std::string& line, std::vector<std::string>& res);
std::vector<std::string> InitialValueSplit(const std::string& line);

} // namespace parser