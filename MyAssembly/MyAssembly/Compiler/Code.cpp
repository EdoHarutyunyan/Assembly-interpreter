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
{
}

Code::Code(const size_t opcode, const std::string& arg)
	: Code(opcode)
{
	m_leftArg.SetLeftArg(arg);
}

std::ostream& operator<<(std::ostream& os, const Code& c)
{
	os << c.m_opcode << c.m_extension << c.m_leftArg << c.m_rightArg;
	return os;
}

std::istream& operator>>(std::istream& is, Code& c)
{
	is >> c.m_opcode >> c.m_extension >> c.m_leftArg >> c.m_rightArg;
	return is;
}

void Code::SourceCodeGenerator(const std::vector<std::string>& tokens,
	const uint8_t indexOfParsingFile, const size_t instructionIndex)
{
	if (SetExtension(tokens[1]))
	{
		assert(tokens.size() == 4);
		
		SetLeftArg(tokens[2]);
		SetRightArg(tokens[3], indexOfParsingFile, instructionIndex);
	}
	else // if not given extension, the default is exactly DW
	{
		assert(tokens.size() == 3);
		
		SetLeftArg(tokens[1]);
		SetRightArg(tokens[2], indexOfParsingFile);
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
	m_leftArg.SetLeftArg(arg);
}

void Code::SetLeftArg(const std::string& arg, std::vector<std::map<std::string, int8_t>>& labels,
	uint8_t indexOfParsingFile)
{
	auto it = labels[indexOfParsingFile].find(arg);

	if (it != labels[indexOfParsingFile].end())
	{
		m_leftArg.m_operand = it->second;
	}
	else
	{
		labels[indexOfParsingFile].insert({ arg, -1 });
	}
}

void Code::SetRightArg(const std::string& arg,
	const uint8_t indexOfParsingFile, const size_t instructionIndex)
{
	m_rightArg.SetRightArg(arg, indexOfParsingFile, instructionIndex);
}

size_t Code::GetOpcode() const
{
	return m_opcode;
}

size_t Code::GetExtension() const
{
	return m_extension;
}

arg::Arg Code::GetRightArg() const
{
	return m_rightArg;
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
	Arg::Arg()
		: m_type(Type::FromMemory)
		, m_operand(0)
	{
	}
	void Arg::SetLeftArg(const std::string& arg)
{
	std::stringstream ss;
	char firstSimbol;
	size_t regIndex{};

	ss << arg;
	ss >> firstSimbol;
	ss >> regIndex;

	if (firstSimbol == 'R')
	{
		m_type = Type::FromGeneralPorposeRegister;
	}
	else if (firstSimbol == 'A')
	{
		m_type = Type::FromAddressRegister;
	}

	m_operand = static_cast<int16_t>(regIndex);
}

void Arg::SetRightArg(const std::string& arg, 
	const uint8_t indexOfParsingFile, const size_t instructionIndex)
{
	std::stringstream ss;
	char firstSimbol;
	size_t regIndex{};

	ss << arg;
	ss >> firstSimbol;

	auto it = parsedfile::symbol_tables[indexOfParsingFile].find(arg);
	if (it != parsedfile::symbol_tables[indexOfParsingFile].end())
	{
		m_type = Type::FromMemory;
		m_operand = std::get<0>(it->second);

		if (m_operand < 0)
		{
			parsedfile::unresolvedSymbols[indexOfParsingFile][it->first] = instructionIndex;
		}
		return;
	}
	else
	{
		if (firstSimbol == 'R')
		{
			m_type = Type::FromGeneralPorposeRegister;
		}
		else if (firstSimbol == 'A')
		{
			m_type = Type::FromAddressRegister;
		}

		ss >> regIndex;
	}

	m_operand = static_cast<int16_t>(regIndex);
}

int16_t Arg::GetOperand() const
{
	return m_operand;
}

void Arg::SetOperand(const int16_t operand)
{
	m_operand = operand;
}

std::ostream& operator<<(std::ostream& os, const Arg& a)
{
	os << static_cast<int8_t>(a.m_type) << a.m_operand;
	return os;
}

std::istream& operator>>(std::istream& is, Arg& a)
{
	uint8_t type;
	if (is >> type)
	{
		a.m_type = static_cast<Type>(type);
	}
	is >> a.m_operand;

	return is;
}

} // namespace arg
} // namespace code