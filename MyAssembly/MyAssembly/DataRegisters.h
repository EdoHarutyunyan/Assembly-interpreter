#pragma once

#include <vector>
#include <map>
#include "decl.h"

class DataRegisters 
{
public:
	DataRegisters()
		: m_dataRegisters{}
	{
	}
	byte m_dataRegisters[64];
};
