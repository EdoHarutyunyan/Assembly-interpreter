#include "Processor.h"
#include <cassert>

namespace processor
{

Processor::Processor(const std::vector<code::Code>& instruction, memory::Memory* ram)
	: m_cpu{new CPU(ram)}
	, m_instruction{instruction}
{
}

Processor::~Processor()
{
	delete m_cpu;
}

void Processor::Execute(const size_t entryPoint)
{
	m_cpu->Execute(entryPoint, m_instruction);
}

}//namespace processor
