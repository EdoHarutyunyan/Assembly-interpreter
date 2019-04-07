#pragma once
#include "decl.h"

#include <vector>

class AddressRegisters
{
public:
	AddressRegisters()
		: aReg{}
	{
		aReg.resize(6);
	}
	~AddressRegisters() = default;

	std::vector<byte> aReg;
};

