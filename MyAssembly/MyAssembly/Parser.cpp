#include "Parser.h"
#include "Command.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <map>
#include <unordered_map>
#include <set>

namespace parser
{

using namespace parsedfile;
	
Parser::Parser(const size_t& parsingFilesCount)
	: m_offsets(parsingFilesCount)
	, m_parsedFiles(parsingFilesCount)
	, m_funcDefinitionMaps(parsingFilesCount)
	, m_indexOfParsingFile(0u)
{
	symbol_tables.resize(parsingFilesCount);
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
	auto it = m_funcDefinitionMaps[m_indexOfParsingFile].find(s);
	
	if (it != m_funcDefinitionMaps[m_indexOfParsingFile].end())
	{
		m_parsedFiles[m_indexOfParsingFile].m_entryPoint = it->second;
	}
}
	
ParsedFiles Parser::GetParsedFiles() const
{
	return m_parsedFiles;
}

FuncDefinitionMaps Parser::GetFuncDefinitionMaps() const
{
	return m_funcDefinitionMaps;
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
		UpdateSymbolsTable(tokens[1], m_offsets[m_indexOfParsingFile], m_indexOfParsingFile);
	}

	switch (type_map[tokens[0]])
	{
	case Type::CHAR:
	{
		if (isForwardDeclaration)
		{
			tokens[1].pop_back();

			// name -> -1
			UpdateSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
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
			UpdateSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
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
			UpdateSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
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
			UpdateSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
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
			UpdateSymbolsTable(tokens[1], -1, m_indexOfParsingFile);
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
	//std::set<std::string /*name*/> funcDeclaration;
	std::map<std::string /*labelName*/, size_t /*index*/> labels;
	std::map<std::string /*commandName*/, size_t /*index*/> commandMap;
	mapInit(commandMap);

	size_t instructionIndex = 0u;
	
	for (size_t i = 0; i < codeSegment.size(); ++i)
	{
		split(codeSegment[i], tokens);
	
		if (tokens[0] == "Func") // is function
		{
			if (tokens[1].back() == ';') // forward declaration
			{
				tokens[1].pop_back();
				symbol_tables[m_indexOfParsingFile].insert({ tokens[1], -1 });
			}
			else if (tokens[1].back() == ':') // definition
			{
				auto def_it = m_funcDefinitionMaps[m_indexOfParsingFile].find(tokens[1]);
	
				if (def_it != m_funcDefinitionMaps[m_indexOfParsingFile].end())
				{
					throw std::invalid_argument(tokens[1] + "redefinition.");
				}
				else
				{
					tokens[1].pop_back();
					m_funcDefinitionMaps[m_indexOfParsingFile].insert({ tokens[1], instructionIndex });
				}
			}
			else
			{
				auto dec_it = symbol_tables[m_indexOfParsingFile].find(tokens[1]);
				auto def_it = m_funcDefinitionMaps[m_indexOfParsingFile].find(tokens[1]);
	
				if (dec_it == symbol_tables[m_indexOfParsingFile].end())
				{
					throw std::invalid_argument("Identifier " + tokens[1] + " is undefined.");
				}
				else if (def_it != m_funcDefinitionMaps[m_indexOfParsingFile].end())
				{
					throw std::invalid_argument(tokens[1] + "redefinition.");
				}
				else
				{
					//m_parsedFiles[m_indexOfParsingFile].m_instruction[def_it->second].SetROper(i); 
	
					tokens[1].pop_back();
					m_funcDefinitionMaps[m_indexOfParsingFile].insert({ tokens[1], instructionIndex });
				}
			} 
			++instructionIndex;
			tokens.clear();
			continue;
		}
	
		char lastChar = tokens[0].back();
		if (lastChar == ':') // is Label
		{
			auto it = labels.find(tokens[0]);
			if (it != labels.end())
			{
				// if operand is a label and was declared earlier
				m_parsedFiles[m_indexOfParsingFile].m_instruction[it->second].SetLOper(i);
			}
			else
			{
				labels.insert({tokens[0], i});
			}
			continue;
		}
	
		switch (commandMap[tokens[0]]) // is Command
		{
		//case commandKeys::eNOP:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eNOP);
		//	break;
		//}
		//case commandKeys::eBREAK:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eBREAK);
		//	break;
		//}
		case commandKeys::eEND:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eEND));
			break;
		}
		case commandKeys::eJUMP:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eJUMP));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
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
		//case commandKeys::eGFLR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eGFLR);
		//	break;
		//}
		//case commandKeys::eSFLR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSFLR);
		//	break;
		//}
		case commandKeys::eLOAD:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eLOAD));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSTORE:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSTORE));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		//case commandKeys::eLDREL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eLDREL);
		//	break;
		//}
		//case commandKeys::eSTREL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSTREL);
		//	break;
		//}
		//case commandKeys::ePUSHSF:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, ePUSHSF);
		//	break;
		//}
		//case commandKeys::ePUSHA:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, ePUSHA);
		//	break;
		//}
		//case commandKeys::ePOP:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, ePOP);
		//	break;
		//}
		case commandKeys::eASSIGN:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eASSIGN));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		//case commandKeys::eSET:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSET);
		//	break;
		//}
		//case commandKeys::eMOVE:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eMOVE);
		//	break;
		//}
		//case commandKeys::eSWAP:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSWAP);
		//	break;
		//}
		//case commandKeys::eINC:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eINC);
		//	break;
		//}
		//case commandKeys::eDEC:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eDEC);
		//	break;
		//}
		//case commandKeys::eTEST:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eTEST);
		//	break;
		//}
		//case commandKeys::eCMP:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eCMP);
		//	break;
		//}
		//case commandKeys::eIN:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eIN);
		//	break;
		//}
		//case commandKeys::eOUT:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eOUT);
		//	break;
		//}
		//case commandKeys::eAND:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eAND);
		//	break;
		//}
		//case commandKeys::eOR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eOR);
		//	break;
		//}
		//case commandKeys::eXOR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eXOR);
		//	break;
		//}
		//case commandKeys::eNAND:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eNAND);
		//	break;
		//}
		//case commandKeys::eNOR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eNOR);
		//	break;
		//}
		//case commandKeys::eNOT:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eNOT);
		//	break;
		//}
		//case commandKeys::eSHL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSHL);
		//	break;
		//}
		//case commandKeys::eSHR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSHR);
		//	break;
		//}
		//case commandKeys::eROL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eROL);
		//	break;
		//}
		//case commandKeys::eROR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eROR);
		//	break;
		//}
		//case commandKeys::eSAL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSAL);
		//	break;
		//}
		//case commandKeys::eSAR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eSAR);
		//	break;
		//}
		//case commandKeys::eRCL:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eRCL);
		//	break;
		//}
		//case commandKeys::eRCR:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eRCR);
		//	break;
		//}
		case commandKeys::eADD:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eADD));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eADC:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eADC));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSUB:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSUB));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eSBB:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eSBB));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eMUL:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eMUL));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eIMUL:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eIMUL));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eDIV:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eDIV));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		case commandKeys::eIDIV:
		{
			m_parsedFiles[m_indexOfParsingFile].m_instruction.push_back(code::Code(eIDIV));
			m_parsedFiles[m_indexOfParsingFile].m_instruction.back().SourceCodeGenerator(tokens, m_funcDefinitionMaps[m_indexOfParsingFile], m_indexOfParsingFile);
			break;
		}
		//case commandKeys::eNEG:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eNEG);
		//	break;
		//}
		//case commandKeys::eCAST:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, eCAST);
		//	break;
		//}
		//case commandKeys::ePRINT:
		//{
		//	m_instruction.push_back(code::Code());
		//	m_instruction.back().SourceCodeGenerator(tokens, funcDeclaration, funcDefinition, ePRINT);
		//	break;
		//}
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
