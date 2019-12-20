#include "Linker.h"
#include <climits>

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
	size_t dataSize = 0u;
	bool isOneStackSize = false;
	bool isOneEntryPoint = false;
	
	if (auto weakPtr = m_parser.lock())
	{
		parser::FuncDefinitionMaps funcDefinitionMaps = weakPtr->GetFuncDefinitionMaps();
		parser::ParsedFiles parsedFiles = std::forward<parser::ParsedFiles>(weakPtr->GetParsedFiles());
		
		for (size_t i = 0; i < parsedFiles.size(); ++i)
		{
			if (parsedFiles[i].m_stackSize != 0)
			{
				if (isOneStackSize)
				{
					throw new std::exception("Linker::ToLink(): 2 or more StackSizes.");
				}

				parsedFile.m_stackSize = parsedFiles[i].m_stackSize;
				isOneStackSize = true;
			}
			if (!isOneStackSize)
			{
				throw new std::exception("Linker::ToLink(): StackSize not found.");
			}

			symbol_tables[i].reserve(6);
			//for (size_t j = 0; j < symbol_tables[i].size(); j++)
			//{
			//	if(symbol_tables[i])
			//	for (size_t l = 0; l < symbol_tables[i].size(); l++)
			//	{

			//	}
			//}





			parsedFile.m_dataStorage.resize(dataSize + parsedFiles[i].m_dataStorage.size());

			for (size_t j = 0; j < parsedFiles[i].m_dataStorage.size(); ++j)
			{
				parsedFile.m_dataStorage[j + dataSize] = parsedFiles[i].m_dataStorage[j];
			}

			dataSize = parsedFiles[i].m_dataStorage.size();

			if (parsedFiles[i].m_entryPoint != 0)
			{
				if (isOneEntryPoint)
				{
					throw new std::exception("Linker::ToLink(): 2 or more EntryPoints.");
				}

				parsedFile.m_entryPoint = parsedFiles[i].m_entryPoint;
				isOneEntryPoint = true;
			}
			if (!isOneEntryPoint)
			{
				throw new std::exception("Linker::ToLink(): EntryPoint not found.");
			}
		}

		// 2 checks
		// 2 merges
	}

	return parsedFile;
}

std::unordered_map<std::string, size_t> Linker::ToLinkSymbolTables()
{
	std::unordered_map<std::string, size_t> symbolTable;
	std::vector<std::string> unresolvedSymbols;

	for (size_t i = 0; i < symbol_tables.size(); ++i)
	{
		for (auto it = symbol_tables[i].begin(); it != symbol_tables[i].end(); ++it)
		{
			if (it->second == -1)
			{
				unresolvedSymbols.push_back(it->first);
			}
			else
			{
				for (const auto& unresolvedSymbol : unresolvedSymbols)
				{
					if (std::strcmp(it->first.c_str(), unresolvedSymbol.c_str()) == 0)
					{

					}
				}
			}
		}
	}
	

	return symbolTable;
}

} // namespace linker