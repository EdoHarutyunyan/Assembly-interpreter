#pragma once

#include "ParsedFile.h"

namespace parser
{

class Parser
{
public:
	Parser();
	~Parser() = default;

	void Start(const std::vector<std::string>& file);

	void StackSizeParser(const std::string& stackSizeSegment);
	void DataParser(const std::vector<std::string>& dataSegment);
	std::unordered_map<std::string, size_t> CodeParser(const std::vector<std::string>& codeSegment);
	void EntryPointParser(
		const std::string& entryPointSegment, 
		const std::unordered_map<std::string, size_t>& funcDefinitionMap);

	ParsedFile GetResult() const;

private:
	void DevideIntoParts(
		const std::vector<std::string>& file,
		std::string& stackSize,
		std::vector<std::string>& dataSegment,
		std::vector<std::string>& codeSegment,
		std::string& entryPoint);
	void WriteDataToDataStorage(const std::vector<std::string>& tokens);
	size_t DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& numInitList);

private:
	size_t m_offset;
	ParsedFile m_result;
};

void split(const std::string& line, std::vector<std::string>& res);
std::vector<std::string> InitialValueSplit(const std::string& line);

}// namespace parser