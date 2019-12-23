#include "Interpreter.h"

namespace interpreter
{

Interpreter::Interpreter(const std::string& binaryFilePath)
	: m_vm(std::make_unique<virtualmachine::VM>())
{
}

void Interpreter::Start()
{
	m_vm->Start();
}

} // namespace interpreter
