#pragma once

#include "decl.h"
#include "Code.h"

#include <vector>

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
	void CodeParser(const std::vector<std::string>& codeSegment);
	void EntryPointParser(const std::string& entryPointSegment);

	std::vector<byte> getDataStorage() const;
	size_t setStackSize() const;

private:
	void DevideIntoParts(
		const std::vector<std::string>& file,
		std::string& stackSize,
		std::vector<std::string>& dataSegment,
		std::vector<std::string>& codeSegment,
		std::string& entryPoint);
	void WriteDataToDataStorage(const std::vector<std::string>& tokens);
	size_t DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& numInitList);

	void SourceCodeGenerator(const std::vector<std::string>& tokens);

private:
	size_t m_stackSize;

	std::vector<byte> m_dataStorage;
	size_t m_offset;

	std::vector<code::Code> m_instruction;
	size_t m_entryPoint;
};

void split(const std::string& line, std::vector<std::string>& res);
std::vector<std::string> InitialValueSplit(const std::string& line);

}// namespace parser