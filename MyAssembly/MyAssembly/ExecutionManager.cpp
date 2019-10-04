#include "ExecutionManager.h"

namespace manager
{

ExecutionManager::ExecutionManager(const std::string& file)
	: m_interpreter{ nullptr }
	, m_compiler{ new compiler::Compiler{file} }
{
}

ExecutionManager::~ExecutionManager()
{
	delete m_interpreter;
	delete m_compiler;
}

void ExecutionManager::Start()
{
	m_compiler->Start();

	const ParsedFile parsingResult = m_compiler->getParsingResult();

	m_interpreter = new interpreter::Interpreter(parsingResult);
	m_interpreter->Start(parsingResult.m_entryPoint);
}

}// namespace manager
