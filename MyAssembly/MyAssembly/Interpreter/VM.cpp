#include "VM.h"

namespace virtualmachine
{
VM::VM()
	: m_memory(nullptr)
	, m_proccessor(std::make_unique<processor::Processor>())
{
}

void VM::Start()
{
}

} // namespace virtualmachine
