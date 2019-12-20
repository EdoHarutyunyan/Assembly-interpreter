#include "Code.h"
#include "ParsedFile.h"

#include <sstream>
#include <cassert>
#include <unordered_map>

namespace code
{

Code::Code(const size_t opcode)
	: m_opcode{opcode}
	, m_extension{DWORD}
	, m_leftArg(nullptr)
	, m_rightArg(nullptr)
{
}

Code::Code(const size_t opcode, const std::string& arg)
	: m_opcode{ opcode }
	, m_extension{ DWORD }
	, m_leftArg(std::make_unique<arg::Arg>(arg))
	, m_rightArg(nullptr)
{
}

void Code::SourceCodeGenerator(const std::vector<std::string>& tokens, 
	std::unordered_map<std::string, size_t>& funcDefinition, const size_t indexOfParsingFile)
{
	if (SetExtension(tokens[1]))
	{
		assert(tokens.size() == 4);
		
		SetLeftArg(tokens[2]);
		SetRightArg(tokens[3], funcDefinition, indexOfParsingFile);
	}
	else // if not given extension, the default is exactly DW
	{
		assert(tokens.size() == 3);
		
		SetLeftArg(tokens[1]);
		SetRightArg(tokens[2], funcDefinition, indexOfParsingFile);
	}
}

bool Code::SetExtension(const std::string& extension)
{
	auto findIt = extensionTable.find(extension);
	if (findIt != extensionTable.end())
	{
		m_extension = extensionTable[extension];
		return true;
	}

	return false;
}

void Code::SetLeftArg(const std::string& arg)
{
	m_leftArg = std::make_unique<arg::Arg>(arg);
}

void Code::SetLeftArg(const std::string& lOper, std::map<std::string, size_t>& labels)
{
	auto it = labels.find(lOper);

	if (it != labels.end())
	{
		m_leftArg->m_operand = it->second;
	}
	else
	{
		labels.insert({ lOper, -1 });
	}
}

void Code::SetRightArg(const std::string& arg,
	std::unordered_map<std::string, size_t>& funcDefinition,
	const size_t indexOfParsingFile)
{
	auto table_it = parsedfile::symbol_tables[indexOfParsingFile].find(arg);
	auto def_it = funcDefinition.find(arg);

	if (table_it != parsedfile::symbol_tables[indexOfParsingFile].end())
	{
		m_rightArg = std::make_unique<arg::Arg>(arg);
	}
	else if (def_it != funcDefinition.end())
	{
		m_rightArg = def_it->second;
	}
	else
	{
		m_rightArg = std::make_unique<arg::Arg>(arg);
	}

}

void Code::SetRightArg(const size_t index)
{
	m_rightArg->m_operand = index;
}

void Code::SetLeftArg(const size_t index)
{
	m_leftArg->m_operand = index;
}

size_t Code::GetOpcode() const
{
	return m_opcode;
}

size_t Code::GetExtension() const
{
	return m_extension;
}

std::unordered_map<std::string, size_t> Code::extensionTable = {
	// CC
	{"xE", xE},
	{"xNE",xNE},
	{"xA", xA},
	{"xAE", xAE},
	{"xB", xB},
	{"xBE", xBE},
	{"xG", xG},
	{"xGE", xGE},
	{"xL", xL},
	{"xLE", xLE},
	{"xO", xO},
	{"xNO", xNO},
	{"xS", xS},
	{"xNS", xNS},
	// Opsize
	{"BYTE", BYTE},
	{"WORD", WORD},
	{"DWORD", DWORD},
	{"QWORD", QWORD}
};

namespace arg
{

Arg::Arg(const std::string& arg)
{
	std::stringstream ss;
	char firstSimbol;

	ss << arg;
	ss >> firstSimbol;

	ss >> m_operand; // may be exeption ?????

	if (firstSimbol == 'R')
	{
		m_type = Type::FromGeneralPorposeRegister;
	}
	else if (firstSimbol == 'A')
	{
		m_type = Type::FromAddressRegister;
	}
	else
	{
		m_type = Type::FromMemory;
		m_operand = 0u;
	}
}

} // namespace arg
} // namespace code