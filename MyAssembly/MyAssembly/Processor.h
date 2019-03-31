#pragma once
#include "CPU.h"

namespace processor
{

class Processor
{
public:
	Processor();
	~Processor();

private:
	cpu::CPU* m_cpu;
};

}//namespace processor 

