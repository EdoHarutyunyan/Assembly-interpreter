#pragma once

#include "CPU.h"
#include "../Compiler/Code.h"

namespace processor
{

using CPUPtr = std::unique_ptr<CPU>;

class Processor
{
public:
	Processor();
	~Processor() = default;

	void Execute();

private:
	CPUPtr m_cpu;
};

} //namespace processor 

