#include "Interpreter.h"

namespace interpreter
{

Interpreter::Interpreter(const ParsedFile& parsingResult)
	: vm{ new virtualmachine::VM{parsingResult} }
{
}

Interpreter::~Interpreter()
{
	delete vm;
}

void Interpreter::Start(const size_t entryPoint)
{
	vm->Start(entryPoint);
}

}//namespace interpreter
