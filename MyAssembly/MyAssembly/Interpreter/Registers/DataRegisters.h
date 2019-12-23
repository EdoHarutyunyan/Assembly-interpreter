#pragma once

#include <vector>
#include <map>

#include "../src/decl.h"

class DataRegisters 
{
public:
	DataRegisters()
		: m_dataRegisters{}
	{
		m_dataRegisters.resize(64);
	}
	std::vector<byte> m_dataRegisters;
};
