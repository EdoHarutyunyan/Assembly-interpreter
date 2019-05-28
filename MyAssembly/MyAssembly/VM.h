#pragma once
#include "ParsedFile.h"

#include "Processor.h"
#include "Memory.h"

namespace virtualmachine
{

class VM
{
public:
	explicit VM(const ParsedFile& parsedFile);

	~VM();

	void Start(size_t entryPoint);

private:
	memory::Memory* m_memory;
	processor::Processor* m_proccessor;
};

}//namespace virtualmachine
