#pragma once
#include "Registers.h"

class Command
{
public:
	virtual void Execute(Registers& registers) = 0;
	virtual ~Command() {}
};
