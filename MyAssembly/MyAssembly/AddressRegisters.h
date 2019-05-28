#pragma once
#include "decl.h"

#include <vector>

class AddressRegisters
{
public:
	AddressRegisters()
		: aReg{}
	{
		aReg.resize(8);
	}
	~AddressRegisters() = default;

	std::vector<byte> aReg;
};

