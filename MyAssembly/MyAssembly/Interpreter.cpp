#include "Interpreter.h"
#include "CommandNode.h"

#include <vector>
#include <cassert>

namespace interpreter
{

Interpreter::Interpreter()
	: vm{new virtualmachine::VM()}
{
}

Interpreter::~Interpreter()
{
	delete vm;
}

void Interpreter::Start()
{
	//vm->Start(ASM->Tokenizer(ASM->ReadFromFile()));
}

}//namespace interpreter
