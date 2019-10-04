#pragma once
#include "decl.h"
#include "Code.h"

#include <vector>

class ParsedFile
{
public:
	ParsedFile()
		: m_stackSize(0u)
		, m_dataStorage(1024)
		, m_entryPoint(0u)
	{
	}

public:
	size_t m_stackSize;
	std::vector<byte> m_dataStorage;
	std::vector<code::Code> m_instruction;
	size_t m_entryPoint;
};
