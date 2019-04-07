#include "VM.h"
#include "CommandNode.h"

namespace virtualmachine
{

VM::VM()
	: procc{ new processor::Processor() }
	, mem{new memory::Memory()}
{
}


VM::~VM()
{
	delete procc;
	delete mem;
}

void VM::Start(std::vector<BaseCommand*> ast)
{
	procc->Execute(ast);
}

}//namespace virtualmachine

