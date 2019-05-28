#pragma once
#include "Interpreter.h"
#include "Compiler.h"

namespace manager
{

class ExecutionManager
{
public:
	explicit ExecutionManager(const std::string& file);
	~ExecutionManager();

	void Start();

private:
	interpreter::Interpreter* m_interpreter;
	compiler::Compiler* m_compiler;
};

}//namespace manager
