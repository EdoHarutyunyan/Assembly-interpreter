#include "Interpreter.h"
#include "CommandNode.h"

#include <vector>
#include <cassert>

namespace interpreter
{

Interpreter::Interpreter(std::string asmName)
	: ASM{new fileio::FileIO(asmName)}
	, vm{new virtualmachine::VM()}
{
}

Interpreter::~Interpreter()
{
	delete ASM;
	delete vm;
}

void Interpreter::Start()
{
	vm->Start(ASM->Tokenizer(ASM->ReadFromFile()));
}

}//namespace interpreter
