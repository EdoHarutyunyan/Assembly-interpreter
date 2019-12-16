#include "Interpreter.h"

namespace interpreter
{

Interpreter::Interpreter(/*const std::fstream& binaryFile*/)
	: m_vm(std::make_unique<virtualmachine::VM>())
{
}

void Interpreter::Start()
{
	//m_vm->Start(entryPoint);
}

} // namespace interpreter
