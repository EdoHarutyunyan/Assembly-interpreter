#include "Processor.h"
#include <cassert>

namespace processor
{

Processor::Processor()
	: m_cpu{new CPU()}
{
}

Processor::~Processor()
{
	delete m_cpu;
}

void Processor::Execute(std::vector<BaseCommand*> ast)
{
	while (m_cpu->m_ip != ast.size())
	{
		ast[m_cpu->m_ip]->Execute(*m_cpu);
		++m_cpu->m_ip;
	}
}

}//namespace processor
