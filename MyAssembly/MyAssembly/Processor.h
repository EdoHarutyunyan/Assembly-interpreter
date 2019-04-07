#pragma once
#include "CPU.h"
#include "CommandNode.h"

namespace processor
{

class Processor
{
public:
	Processor();
	~Processor();

	void Execute(std::vector<BaseCommand*> ast);

private:
	CPU* m_cpu;
	//std::vector<Command*> AST;
};

}//namespace processor 

