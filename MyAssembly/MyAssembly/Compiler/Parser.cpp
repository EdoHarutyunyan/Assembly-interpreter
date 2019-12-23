#include "Parser.h"
#include "../src/Command.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <map>
#include <unordered_map>

namespace parser
{

using namespace parsedfile;
	
Parser::Parser(const size_t& parsingFilesCount)
	: m_offsets(parsingFilesCount)
	, m_parsedFiles(parsingFilesCount)
	, m_labels(parsingFilesCount)
	, m_indexOfParsingFile(0u)
{
	symbol_tables.resize(parsingFilesCount);
	unresolvedSymbols.resize(parsingFilesCount);
}

void Parser::Start(const std::vector<std::string>& file)
{
	IsStackSize stackSizeSegment;
	IsDataSegment dataSegment;
	IsCodeSegment codeSegment;
	IsEntryPoint entryPointSegment;

	DevideIntoParts(file, stackSizeSegment, dataSegment, codeSegment, entryPointSegment);

	if (std::get<0>(stackSizeSegment))
	{
		StackSizeParser(std::get<1>(stackSizeSegment));
	}
	if (std::get<0>(dataSegment))
	{
		DataParser(std::get<1>(dataSegment));
	}
	if (std::get<0>(codeSegment))
	{
		CodeParser(std::get<1>(codeSegment));
	}
	if (std::get<0>(entryPointSegment))
	{
		EntryPointParser(std::get<1>(entryPointSegment));
	}

	++m_indexOfParsingFile;
}
	
void Parser::StackSizeParser(const std::string& stackSizeSegment)
{
	const size_t pos = stackSizeSegment.find_last_of(' ');
	const size_t count = stackSizeSegment.length() - pos;
	m_parsedFiles[m_indexOfParsingFile].m_stackSize = std::atoi(stackSizeSegment.substr(pos, count).c_str());
}
	
void Parser::DataParser(const std::vector<std::string>& dataSegment)
{
	std::vector<std::string> tokens;
	
	for (size_t i = 0; i < dataSegment.size(); ++i)
	{
		split(dataSegment[i], tokens);
		WriteDataToDataStorage(std::move(tokens));
		tokens.clear();
	}
	
	m_parsedFiles[m_indexOfParsingFile].m_dataStorage.resize(m_offsets[m_indexOfParsingFile]);
}
	
void Parser::EntryPointParser(const std::string& entryPointSegment)
{
	const size_t pos = entryPointSegment.find_last_of(' ');
	const size_t count = entryPointSegment.length() - pos;
	std::string s = entryPointSegment.substr(pos + 1, count).c_str();
	auto it = symbol_tables[m_indexOfParsingFile].find(s);
	
	if (it != symbol_tables[m_indexOfParsingFile].end() && std::get<0>(it->second) >= 0)
	{
		m_parsedFiles[m_indexOfParsingFile].m_entryPoint = std::get<0>(it->second);
	}
}
	
ParsedFiles Parser::GetParsedFiles() const
{
	return m_parsedFiles;
}

Labels Parser::GetLabels() const
{
	return m_labels;
}

void Parser::DevideIntoParts(
	const std::vector<std::string>& file,
	IsStackSize& stackSize,
	IsDataSegment& dataSegment,
	IsCodeSegment& codeSegment,
	IsEntryPoint& entryPoint)
{
	size_t breakPoint = 0u;
	bool isStackSizeExists = false;
	bool isDataSegmentExists = false;
	bool isCodeSegmentExists = false;
	bool isEntryPointExists = false;

	std::vector<std::string> data;
	std::vector<std::string> code;

	if (file[0].find(".STACK") != std::string::npos)
	{
		isStackSizeExists = true;
		++breakPoint;
	}

	for (size_t i = breakPoint; i < file.size(); ++i)
	{
		if (file[i].empty())
		{
			continue;
		}
		if (file[i] == ".DATA")
		{
			isDataSegmentExists = true;
			continue;
		}
		if (file[i] == ".CODE")
		{
			breakPoint = ++i;
			isCodeSegmentExists = true;
			break;
		}
		if (file[i].find(".MAIN") != std::string::npos)
		{
			isEntryPointExists = true;
			break;
		}

		data.push_back(file[i]);
	}

	for (size_t i = breakPoint; i < file.size(); ++i)
	{
		if (file[i].empty())
		{
			continue;
		}
		if (file[i].find(".MAIN") != std::string::npos)
		{
			isEntryPointExists = true;
			break;
		}

		code.push_back(file[i]);
	}

	stackSize = std::make_tuple(isStackSizeExists, file.front());
	dataSegment = std::make_tuple(isDataSegmentExists, data);
	codeSegment = std::make_tuple(isCodeSegmentExists, code);
	entryPoint = std::make_tuple(isEntryPointExists, file.back());
}
	
void Parser::WriteDataToDataStorage(std::vector<std::string>&& tokens)
{
	std::vector<std::string> initialValue;
	bool isForwardDeclaration = false;

	const size_t offsetFactor = DetermineOffsetSize(tokens, initialValue);

	if (tokens[1].back() == ';')
	{
		isForwardDeclaration = true;
	}
	else
	{
		// name -> offset
		UpdateDataInSymbolsTable(tokens[1], m_offsets[m_indexOfParsingFile], m_indexOfParsingFile);
	}

	switch (type_map[tokens[0]])
	{
	case Type::CHAR:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateDataInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			m_offsets[m_indexOfParsingFile] += sizeof(byte);
		}

		if (tokens.size() > 2) // if given initial value
		{
			std::string initialString = tokens[3].substr(1, tokens[3].length() - 2); // delete '' or ""
	
			// initialize by given value
			for (size_t i = 0; i < initialString.length(); ++i)
			{
				byte* b = &m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]];
	
				*b = initialString[i];
				m_offsets[m_indexOfParsingFile] += sizeof(byte);
			}
	
			m_offsets[m_indexOfParsingFile] += (offsetFactor - initialString.length()) * sizeof(byte);
		}
		else
		{
			m_offsets[m_indexOfParsingFile] += offsetFactor * sizeof(CHAR);
		}
	
		break;
	}
	case Type::BYTE:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateDataInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			m_offsets[m_indexOfParsingFile] += sizeof(byte);
			break;
		}

		// initialize by given value
		for (size_t i = 0; i < initialValue.size(); ++i)
		{
			byte* b = &m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]];
			*b = std::atoi(initialValue[i].c_str());
			m_offsets[m_indexOfParsingFile] += sizeof(byte);
		}
	
		size_t defaultValuesCount = offsetFactor - initialValue.size();
	
		// initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			byte* b = &m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]];
			*b = 0;
			m_offsets[m_indexOfParsingFile] += sizeof(byte);
		}
	
		break;
	}
	case Type::WORD:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateDataInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			m_offsets[m_indexOfParsingFile] += sizeof(word);
			break;
		}

		// initialize by given value
		for (size_t i = 0; i < initialValue.size(); ++i)
		{
			word* w = reinterpret_cast<word*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*w = std::atoi(initialValue[i].c_str());
			m_offsets[m_indexOfParsingFile] += sizeof(word);
		}
	
		size_t defaultValuesCount = offsetFactor - initialValue.size();
	
		// initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			word* w = reinterpret_cast<word*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*w = 0;
			m_offsets[m_indexOfParsingFile] += sizeof(word);
		}
	
		break;
	}
	case Type::DWORD:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateDataInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			m_offsets[m_indexOfParsingFile] += sizeof(dword);
			break;
		}

		// initialize by given value
		for (size_t i = 0; i < initialValue.size(); ++i)
		{
			dword* d = reinterpret_cast<dword*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*d = std::atoi(initialValue[i].c_str());
			m_offsets[m_indexOfParsingFile] += sizeof(dword);
		}
	
		size_t defaultValuesCount = offsetFactor - initialValue.size();
	
		// initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			dword* d = reinterpret_cast<dword*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*d = 0;
			m_offsets[m_indexOfParsingFile] += sizeof(dword);
		}
	
		break;
	}
	case Type::QWORD:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateDataInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			m_offsets[m_indexOfParsingFile] += sizeof(qword);
			break;
		}

		// initialize by given value
		for (size_t i = 0; i < initialValue.size(); ++i)
		{
			qword* q = reinterpret_cast<qword*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*q = std::atoi(initialValue[i].c_str());
			m_offsets[m_indexOfParsingFile] += sizeof(qword);
		}
	
		size_t defaultValuesCount = offsetFactor - initialValue.size();
			
		// initialize by default value
		for (size_t i = 0; i < defaultValuesCount; ++i)
		{
			qword* q = reinterpret_cast<qword*>(&m_parsedFiles[m_indexOfParsingFile].m_dataStorage[m_offsets[m_indexOfParsingFile]]);
			*q = 0;
			m_offsets[m_indexOfParsingFile] += sizeof(qword);
		}
		break;
	}
	default:
		assert(false);
		break;
	}
}
	
size_t Parser::DetermineOffsetSize(const std::vector<std::string>& tokens, std::vector<std::string>& initialValue)
{
	const size_t pos = tokens[1].find('[');
	size_t offsetFactor = 1;
	
	if (tokens.size() > 2 && type_map[tokens[0]] != CHAR) // if given initial value
	{
		initialValue = InitialValueSplit(tokens[3]);
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
				tokens.at(3).length() - 2 : initialValue.size();
		}
	}
	
	return offsetFactor;
}
	
void Parser::CodeParser(const std::vector<std::string>& codeSegment)
{
	using namespace command;
	
	std::vector<std::string> tokens;
	std::map<std::string /*commandName*/, size_t /*index*/> commandMap;
	mapInit(commandMap);

	uint8_t instructionIndex = 0u;
	
	for (size_t i = 0; i < codeSegment.size(); ++i)
	{
		split(codeSegment[i], tokens);
	
		if (tokens[0] == "Func") // is function
		{
			if (tokens[1].back() == ';') // forward declaration
			{
				tokens[1].pop_back();
				UpdateFuncInSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
			}
			else if (tokens[1].back() == ':') // definition
			{
				auto it = symbol_tables[m_indexOfParsingFile].find(tokens[1]);
	
				if (it != symbol_tables[m_indexOfParsingFile].end() && std::get<0>(it->second) >= 0)
				{
					throw std::invalid_argument(tokens[1] + "redefinition.");
				}
				else
				{
					tokens[1].pop_back();
					UpdateFuncInSymbolsTable(tokens[1], instructionIndex, m_indexOfParsingFile);
				}
			}
			else
			{
				auto it = symbol_tables[m_indexOfParsingFile].find(tokens[1]);
	
				if (it == symbol_tables[m_indexOfParsingFile].end())
				{
					throw std::invalid_argument("Identifier " + tokens[1] + " is undefined.");
				}
				else if (std::get<0>(it->second) >= 0)
				{
					throw std::invalid_argument(tokens[1] + " redefinition.");
				}
				else
				{
					std::get<0>(it->second) = instructionIndex;
					std::get<1>(it->second) = true;
					++instructionIndex;
				}
			}
			tokens.clear();
			continue;
		}
	
		char lastChar = tokens[0].back();
		if (lastChar == ':') // is Label
		{
			tokens[0].pop_back();
			auto it = m_labels[m_indexOfParsingFile].find(tokens[0]);
			if (it == m_labels[m_indexOfParsingFile].end())
			{
				m_labels[m_indexOfParsingFile].insert({tokens[0], instructionIndex});
			}
			else if (it->second < 0)
			{
				it->second = instructionIndex;
			}
			tokens.clear();
			continue;
		}
	
		switch (commandMap[tokens[0]]) // is Command
		{
		case commandKeys::eNOP:
		case commandKeys::eBREAK:
			throw new std::exception("Not supported yet.");
		case commandKeys::eEND:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eEND));
			break;
		}
		case commandKeys::eJUMP:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eJUMP));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SetLeftArg(tokens[1], m_labels, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eCALL:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eCALL, tokens[1]));
			break;
		}
		case commandKeys::eRET:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eRET));
			break;
		}
		case commandKeys::eGFLR:
		case commandKeys::eSFLR:
			throw new std::exception("Not supported yet.");
		case commandKeys::eLOAD:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eLOAD));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSTORE:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSTORE));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eLDREL:
		case commandKeys::eSTREL:
		case commandKeys::ePUSHSF:
		case commandKeys::ePUSHA:
		case commandKeys::ePOP:
			throw new std::exception("Not supported yet.");
		case commandKeys::eASSIGN:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eASSIGN));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile, instructionIndex);
			break;
		}
		case commandKeys::eSET:
		case commandKeys::eMOVE:
		case commandKeys::eSWAP:
		case commandKeys::eINC:
		case commandKeys::eDEC:
		case commandKeys::eTEST:
		case commandKeys::eCMP:
		case commandKeys::eIN:
		case commandKeys::eOUT:
		case commandKeys::eAND:
		case commandKeys::eOR:
		case commandKeys::eXOR:
		case commandKeys::eNAND:
		case commandKeys::eNOR:
		case commandKeys::eNOT:
		case commandKeys::eSHL:
		case commandKeys::eSHR:
		case commandKeys::eROL:
		case commandKeys::eROR:
		case commandKeys::eSAL:
		case commandKeys::eSAR:
		case commandKeys::eRCL:
		case commandKeys::eRCR:
			throw new std::exception("Not supported yet.");
		case commandKeys::eADD:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eADD));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eADC:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eADC));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSUB:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSUB));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSBB:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSBB));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eMUL:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eMUL));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_indexOfParsingFile);
			break;
		}
		case commandKeys::eIMUL:
		case commandKeys::eDIV:
		case commandKeys::eIDIV:
		case commandKeys::eNEG:
		case commandKeys::eCAST:
		case commandKeys::ePRINT:
			throw new std::exception("Not supported yet.");
		default:
			assert(false);
			break;
		}

		++instructionIndex;
		tokens.clear();
	}
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
	
// when given initial value by initializer list
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
	
} // namespace parser
