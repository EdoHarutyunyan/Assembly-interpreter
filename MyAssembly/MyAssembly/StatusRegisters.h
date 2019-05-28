#pragma once
#include <vector>

struct StatusRegisters
{
	StatusRegisters()
		: sFlag{}
	{
		sFlag.resize(4);
	}

	std::vector<bool> getFlag() const { return sFlag; };
	
	std::vector<bool> sFlag;
};

enum flags
{
	ZF = 0,
	CF,
	SF,
	OF
};