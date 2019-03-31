#pragma once
#include "Processor.h"
#include "Memory.h"

namespace virtualmachine
{

class VM
{
public:
	VM();
	~VM();

private:
	processor::Processor* procc;
	memory::Memory* memory;
};

}//namespace virtualmachine
