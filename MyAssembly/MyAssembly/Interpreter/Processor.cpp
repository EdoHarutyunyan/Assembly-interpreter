#include "Processor.h"
#include <cassert>

namespace processor
{

Processor::Processor()
	: m_cpu(std::make_unique<CPU>())
{
}

void Processor::Execute()
{
	//m_cpu->Execute();
}

} // namespace processor
