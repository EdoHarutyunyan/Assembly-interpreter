#include "VM.h"

namespace virtualmachine
{
VM::VM(const ParsedFile& parsedFile)
	: m_memory{ new memory::Memory{parsedFile.m_stackSize, parsedFile.m_dataStorage} }
	, m_proccessor{ new processor::Processor{parsedFile.m_instruction, m_memory} }
{
}

VM::~VM()
{
	delete m_memory;
	delete m_proccessor;
}

void VM::Start(const size_t entryPoint)
{
	m_proccessor->Execute(entryPoint);
}

}//namespace virtualmachine
