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

	void Start(std::vector<BaseCommand*> ast);

private:
	processor::Processor* procc;
	memory::Memory* mem;
};

}//namespace virtualmachine
