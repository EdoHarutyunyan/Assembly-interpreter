#pragma once
#include <iostream>
#include <vector>
#include "Interpreter.h"
#include "Compiler.h"


namespace manager
{

using InterpreterPtr = std::unique_ptr<interpreter::Interpreter>;
using CompilerPtr = std::unique_ptr<compiler::Compiler>;

class ExecutionManager
{
public:
	explicit ExecutionManager(std::vector<std::string>&& paths);
	~ExecutionManager() = default;

	void Start();

private:
	InterpreterPtr m_interpreter;
	CompilerPtr m_compiler;
};

} // namespace manager
