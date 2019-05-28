#pragma once
#include "decl.h"
#include "Code.h"

#include <vector>

struct ParsedFile
{
	ParsedFile()
		: stackSize{}
		, dataStorage(1024)
		, instruction{}
		, entryPoint{}
	{
	}

	size_t stackSize;
	std::vector<byte> dataStorage;
	std::vector<code::Code> instruction;
	size_t entryPoint;
};
