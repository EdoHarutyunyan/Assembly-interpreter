#include "Parser.h"
#include "Type.h"
#include "Command.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <map>
#include <unordered_map>
#include <set>

namespace parser
{

using namespace type;

Parser::Parser()
	: m_stackSize{}
	, m_dataStorage(1024)
	, m_offset{}
	, m_instruction{}
	, m_entryPoint{}
{
}

void Parser::Start(const std::vector<std::string>& file)
{
	std::string stackSizeSegment;
	std::vector<std::string> dataSegment;
	std::vector<std::string> codeSegment;
	std::string entryPointSegment;

	DevideIntoParts(file, stackSizeSegment, dataSegment, codeSegment, entryPointSegment);

	StackSizeParser(stackSizeSegment);
	DataParser(dataSegment);
	CodeParser(codeSegment);
	EntryPointParser(entryPointSegment);
}

void Parser::StackSizeParser(const std::string& stackSizeSegment)
{
	size_t pos = stackSizeSegment.find_last_of(' ');
	size_t count = stackSizeSegment.length() - pos;
	m_stackSize = std::atoi(stackSizeSegment.substr(pos, count).c_str());
}

void Parser::DataParser(const std::vector<std::string>& dataSegment)
{
	std::vector<std::string> tokens;

	for (size_t i = 0; i < dataSegment.size(); ++i)
	{
		split(dataSegment[i], tokens);
		WriteDataToDataStorage(tokens);
		tokens.clear();
	}
}

void Parser::EntryPointParser(const std::string& entryPointSegment)
{
	size_t pos = entryPointSegment.find_last_of(' ');
	size_t count = entryPointSegment.length() - pos;
	m_entryPoint = std::atoi(entryPointSegment.substr(pos, count).c_str());
}

void Parser::DevideIntoParts(
	const std::vector<std::string>& file,
	std::string& stackSize,
	std::vector<std::string>& dataSegment,
	std::vector<std::string>& codeSegment,
	std::string& entryPoint)
{
	size_t breakPoint;

	stackSize = file[0];// Size of stack

	dataSegment.reserve(file.size());
	codeSegment.reserve(file.size());

	for (size_t i = 1; i < file.size(); ++i) // Data partition
	{
		if (file[i].empty() || file[i] == ".DATA")
		{
			continue;
		}
		if (file[i] == ".CODE")
		{
			breakPoint = ++i;
			break;
		}

		dataSegment.push_back(file[i]);
	}

	for (size_t i = breakPoint; i < file.size() - 1; ++i) // Code partition
	{
		if (file[i].empty())
		{
			continue;
		}

		codeSegment.push_back(file[i]);
	}

	entryPoint = file.back(); // The first instruction
}

void Parser::WriteDataToDataStorage(const std::vector<std::string>& tokens)
{
	std::vector<std::string> numInitList;

	size_t offsetFactor = DetermineOffsetSize(tokens, numInitList);

	// name -> offset
	UpdateTypeTable(tokens[1], m_offset);

	switch (type_map[tokens[0]])
	{
	case Type::CHAR:
	{
		if (tokens.size() > 2)// if given initial value
		{
			std::string initialString = tokens[3].substr(1, tokens[3].length() - 2);// delete '' and ""

			//initialize by value
			for (size_t i = 0; i < initialString.length(); ++i)
			{
				byte* b = &m_dataStorage[m_offset];

				*b = initialString[i];
				m_offset += sizeof(byte);
			}

			m_offset += (offsetFactor - initialString.length()) * sizeof(byte);
		}
		else
		{
			m_offset += offsetFactor * sizeof(CHAR);
		}

		break;
	}
	case Type::BYTE:
	{
		//initialize by value
		for (size_t i = 0; i < numInitList.size(); ++i)
		{
			byte* b = &m_dataStorage[m_offset];
			*b = std::atoi(numInitList[i].c_str());
			m_offset += sizeof(byte);
		}

		size_t defaultValuesCount = offsetFactor - numInitList.size();

		//initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			byte* b = &m_dataStorage[m_offset];
			*b = 0;
			m_offset += sizeof(byte);
		}

		break;
	}
	case Type::WORD:
	{
		//initialize by value
		for (size_t i = 0; i < numInitList.size(); ++i)
		{
			word* w = reinterpret_cast<word*>(&m_dataStorage[m_offset]);
			*w = std::atoi(numInitList[i].c_str());
			m_offset += sizeof(word);
		}

		size_t defaultValuesCount = offsetFactor - numInitList.size();

		//initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			word* w = reinterpret_cast<word*>(&m_dataStorage[m_offset]);
			*w = 0;
			m_offset += sizeof(word);
		}

		break;
	}
	case Type::DWORD:
	{
		//initialize by value
		for (size_t i = 0; i < numInitList.size(); ++i)
		{
			dword* d = reinterpret_cast<dword*>(&m_dataStorage[m_offset]);
			*d = std::atoi(numInitList[i].c_str());
			m_offset += sizeof(dword);
		}

		size_t defaultValuesCount = offsetFactor - numInitList.size();

		//initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			dword* d = reinterpret_cast<dword*>(&m_dataStorage[m_offset]);
			*d = 0;
			m_offset += sizeof(dword);
		}

		break;
	}
	case Type::QWORD:
	{
		//initialize by value
		for (size_t i = 0; i < numInitList.size(); ++i)
		{
			qword* q = reinterpret_cast<qword*>(&m_dataStorage[m_offset]);
			*q = std::atoi(numInitList[i].c_str());
			m_offset += sizeof(qword);
		}

		size_t defaultValuesCount = offsetFactor - numInitList.size();
		
		//initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			qword* q = reinterpret_cast<qword*>(&m_dataStorage[m_offset]);
			*q = 0;
			m_offset += sizeof(qword);
		}
		break;
	}
	default:
		assert(false);
		break;
	}
}

size_t Parser::DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& numInitList)
{
	size_t pos = tokens[1].find('[');
	size_t offsetFactor = 1;

	if (tokens.size() > 2 && type_map[tokens[0]] != CHAR)// if given initial value
	{
		numInitList = InitialValueSplit(tokens[3]);
	}

	if (pos < tokens[1].size())
	{
		size_t elemCount = tokens[1].length() - pos - 2;

		if (elemCount > 0)
		{
			offsetFactor = std::atoi(tokens[1].substr(pos + 1, elemCount).c_str());
		}
		else
		{
			offsetFactor = type_map[tokens[0]] == CHAR ?
				tokens.at(3).length() - 2 : numInitList.size();
		}
	}

	return offsetFactor;
}

void Parser::CodeParser(const std::vector<std::string>& codeSegment)
{
	using namespace command;

	std::vector<std::string> tokens;

	std::map<std::string, size_t> commandMap;
	mapInit(commandMap);

	std::set<std::string /*name*/> f_declaration;
	std::unordered_map<std::string /*name*/, size_t /*index*/> f_definition;

	size_t instructionIndex = 0;

	for (size_t i = 0; i < codeSegment.size(); ++i)
	{
		split(codeSegment[i], tokens);

		if (tokens[0] == "Func")
		{
			if (tokens[1].back() == ';') // declaration
			{
				f_declaration.insert(tokens[1]);
				break;
			}
			else // definition
			{
				auto it = f_definition.find(tokens[1]);

				if (it != f_definition.end())
				{
					it->second = i;
					break;
				}

				f_declaration.insert({ tokens[1], i });
			}
		}

		auto table_it = type::type_table.find(tokens[2]);
		auto dec_it = f_declaration.find(tokens[2]);
		auto def_it = f_definition.find(tokens[2]);

		size_t lOperand;
		size_t rOperand;

		switch (commandMap[tokens[0]])
		{
		case commandKeys::eASSIGN:
		{
			if ((table_it != type::type_table.end()
				&& dec_it != f_declaration.end())
			 || (table_it != type::type_table.end()
				&& def_it != f_definition.end()))
			{
				throw std::invalid_argument(tokens[2] + ": redefinition");
			}
			if (table_it != type::type_table.end())
			{
				rOperand = table_it->second;
			}
			else if (def_it != f_definition.end()) 
			{
				rOperand = def_it->second;
			}
			else if (dec_it != f_declaration.end())
			{
				f_definition.insert({ tokens[2], i });
			}
			else 
			{
				std::stringstream ss;
				char c;
				ss << tokens[2];
				ss >> c;
				ss >> rOperand;
				if (c == 'A')
				{
					rOperand += code::addressRegsStartPos;
				}
			}
			//else
			//{
			//	throw std::invalid_argument(tokens[2] + ": undeclared identifier");
			//}
			break;
		}
			//m_instruction.push_back(code::Code(tokens[2], tokens[3]),tokens[1]);//string mek el DW verjum by default
		case commandKeys::eADD:
		{

			//m_instruction.push_back(code::Code({ tokens[2], tokens[3]) }, tokens[1]);//string mek el DW verjum by default
			break;
		}
		case commandKeys::eCMP:
			break;
		case commandKeys::eDIV:
			break;
		default:
			break;
		}
		tokens.clear();
	}
}

void Parser::SourceCodeGenerator(const std::vector<std::string>& tokens)
{
	
}

std::vector<byte> Parser::getDataStorage() const
{
	return m_dataStorage;
}

size_t Parser::setStackSize() const
{
	return m_stackSize;
}

void split(const std::string& line, std::vector<std::string>& res)
{
	std::stringstream ss(line);
	std::string item;

	while (std::getline(ss, item, ' '))
	{
		//that not to miss the spaces in char[]
		if (item[0] == '\'' || item[0] == '\"')
		{
			std::string buff;
			ss >> buff;
			if (!buff.empty())
			{
				item += ' ' + buff;
			}
		}
		if (item.length() > 0)
		{
			res.push_back(item);
		}
	}
}

std::vector<std::string> InitialValueSplit(const std::string& line)
{
	std::vector<std::string> initialValue;
	std::stringstream ss(line);
	std::string item;

	auto hexToDec = [&item]()->std::string {

		qword num;
		std::stringstream buff;

		buff << std::hex << item;
		buff >> num;

		return std::to_string(num);
	};

	while (std::getline(ss, item, ','))
	{
		std::string hex = item.substr(0, 2);
	
		if (hex == "0x")
		{
			item = hexToDec();
		}
		if (item.length() > 0)
		{
			initialValue.push_back(item);
		}
	}

	return initialValue;
}

}// namespace parser
