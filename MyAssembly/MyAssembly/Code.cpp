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
	, m_lOper{}
	, m_rOper{}
{
}

Code::Code(const size_t opcode, const std::string& reg)
	: m_opcode{ opcode }
	, m_extension{ DWORD }
	, m_lOper{}
{
	m_lOper = RegInit(reg);
}

void Code::SourceCodeGenerator(const std::vector<std::string>& tokens, 
	std::unordered_map<std::string, size_t>& funcDefinition, const size_t indexOfParsingFile)
{
	if (SetExtension(tokens[1]))
	{
		assert(tokens.size() == 4);
		
		SetLOper(tokens[2]);
		SetROper(tokens[3], funcDefinition, indexOfParsingFile);
	}
	else // if not given extension, the default is exactly DW
	{
		assert(tokens.size() == 3);
		
		SetLOper(tokens[1]);
		SetROper(tokens[2], funcDefinition, indexOfParsingFile);
	}
}

bool Code::SetExtension(const std::string& ext)
{
	auto findIt = extensionTable.find(ext);
	if (findIt != extensionTable.end())
	{
		m_extension = extensionTable[ext];
		return true;
	}

	return false;
}

void Code::SetLOper(const std::string& reg)
{
	m_lOper = RegInit(reg);
}

void Code::SetLOper(const std::string& lOper, std::map<std::string, size_t>& labels)
{
	auto it = labels.find(lOper);

	if (it != labels.end())
	{
		m_lOper = it->second;
	}
	else
	{
		labels.insert({ lOper, -1 });
	}
}

void Code::SetROper(const std::string& rOp,
	std::unordered_map<std::string, size_t>& funcDefinition,
	const size_t indexOfParsingFile)
{
	auto table_it = parsedfile::symbol_tables[indexOfParsingFile].find(rOp);
	auto def_it = funcDefinition.find(rOp);

	if (table_it != parsedfile::symbol_tables[indexOfParsingFile].end())
	{
		m_rOper = table_it->second;
	}
	else if (def_it != funcDefinition.end())
	{
		m_rOper = def_it->second;
	}
	else
	{
		m_rOper = RegInit(rOp);
	}

}

void Code::SetROper(const size_t index)
{
	m_rOper = index;
}

void Code::SetLOper(const size_t index)
{
	m_lOper = index;
}

size_t Code::GetOpcode() const
{
	return m_opcode;
}

size_t Code::GetExtension() const
{
	return m_extension;
}

size_t Code::GetlOper() const
{
	return m_lOper;
}

size_t Code::GetrOper() const
{
	return m_rOper;
}

size_t Code::RegInit(const std::string& reg)
{
	std::stringstream ss;
	char firstSimbol;
	
	size_t returnValue;

	ss << reg;
	ss >> firstSimbol;

	if (firstSimbol == 'R') // General purpose register
	{
		ss >> returnValue;
	}
	else if (firstSimbol == 'A') // Address register
	{
		ss >> returnValue;
		returnValue += code::addressRegsStartPos;
	}
	else
	{
		throw std::invalid_argument(returnValue + ": undeclared identifier");
	}

	return returnValue;
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
	{"QWORD", QWORD},
};

const size_t addressRegsStartPos = 70;

}//namespace code