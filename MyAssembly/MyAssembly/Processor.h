#pragma once

#include "CPU.h"
#include "Code.h"

namespace processor
{

class Processor
{
public:
	Processor(const std::vector<code::Code>& instruction, memory::Memory* ram);
	~Processor();

	void Execute(size_t entryPoint);

private:
	CPU* m_cpu;
	std::vector<code::Code> m_instruction;
};

} //namespace processor 

