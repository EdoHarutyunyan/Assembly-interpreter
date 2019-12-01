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

	const std::vector<std::string> bynaryFile = m_compiler->GetBynaryFile();

	//m_interpreter = new interpreter::Interpreter(bynaryFile);
	//m_interpreter->Start(parsingResult.m_entryPoint);
}

}// namespace manager
