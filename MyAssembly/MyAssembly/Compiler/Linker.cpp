#include "Linker.h"
#include <climits>

#include "../src/Command.h"

namespace linker
{

using namespace parsedfile;

Linker::Linker(ParserPtr&& parser)
	: m_parser(parser)
{
}

ParsedFile Linker::ToLink()
{
	ParsedFile parsedFile;
	Symbols symbolTable;
	size_t dataSize{};
	size_t codeSize{};
	size_t localDataSize{};
	size_t localCodeSize{};
	bool isOneStackSize = false;
	bool isOneEntryPoint = false;
	
	if (auto weakPtr = m_parser.lock())
	{
		parser::ParsedFiles parsedFiles = weakPtr->GetParsedFiles();
		parser::Labels labels = weakPtr->GetLabels();

		for (size_t i = 0; i < parsedFiles.size(); ++i)
		{
			if (parsedFiles[i].m_stackSize != -1)
			{
				if (isOneStackSize)
				{
					throw new std::exception("Linker::ToLink(): 2 or more StackSizes.");
				}

				parsedFile.m_stackSize = parsedFiles[i].m_stackSize;
				isOneStackSize = true;
			}
			if (parsedFiles[i].m_entryPoint != -1)
			{
				if (isOneEntryPoint)
				{
					throw new std::exception("Linker::ToLink(): 2 or more EntryPoints.");
				}

				parsedFile.m_entryPoint = parsedFiles[i].m_entryPoint;
				isOneEntryPoint = true;
			}

			parsedFile.m_dataStorage.resize(dataSize + parsedFiles[i].m_dataStorage.size());
			parsedFile.m_instruction.resize(codeSize + parsedFiles[i].m_instruction.size());

			for (size_t j = 0; j < parsedFiles[i].m_dataStorage.size(); ++j)
			{
				parsedFile.m_dataStorage[j + dataSize] = parsedFiles[i].m_dataStorage[j];
			}

			for (size_t j = 0; j < parsedFiles[i].m_instruction.size(); ++j)
			{
				parsedFile.m_instruction[j + codeSize] = parsedFiles[i].m_instruction[j];
			}

			for (auto it = symbol_tables[i].begin(); it != symbol_tables[i].end(); ++it)
			{
				if (std::get<0>(it->second) < 0)
				{
					bool isFoundInTable = false;

					for (size_t l = 0; l < symbol_tables.size(); ++l)
					{
						//if (l == i)
						//{
						//	localDataSize += parsedFiles[l].m_dataStorage.size();
						//	localCodeSize += parsedFiles[l].m_instruction.size();
						//	continue;
						//}

						auto found = symbol_tables[l].find(it->first);
						if (found != symbol_tables[l].end() && std::get<0>(found->second) >= 0)
						{
							isFoundInTable = true;

							if (std::get<1>(found->second))
							{
								symbolTable.insert({ found->first, std::get<0>(found->second) + localCodeSize });
							}
							else
							{
								symbolTable.insert({ found->first, std::get<0>(found->second) + localDataSize });
							}
						}

						localDataSize += parsedFiles[l].m_dataStorage.size();
						localCodeSize += parsedFiles[l].m_instruction.size();
					}
					if (!isFoundInTable)
					{
						throw new std::exception("Unresolved external symbol.");
					}
				}
				else
				{
					if (std::get<1>(it->second))
					{
						symbolTable.insert({ it->first, std::get<0>(it->second) + codeSize });
					}
					else
					{
						symbolTable.insert({ it->first, std::get<0>(it->second) + dataSize });
					}
				}
			}
			dataSize = parsedFiles[i].m_dataStorage.size();
			codeSize = parsedFiles[i].m_instruction.size();

			for (auto& elem : unresolvedSymbols[i])
			{
				auto it = symbolTable.find(elem.first);
				parsedFile.m_instruction[elem.second].GetRightArg().SetOperand(it->second);
			}
		} 

		if (!isOneStackSize)
		{
			throw new std::exception("Linker::ToLink(): StackSize not found.");
		}
		if (!isOneEntryPoint)
		{
			throw new std::exception("Linker::ToLink(): EntryPoint not found.");
		}
	} 

	return parsedFile;
}

} // namespace linker