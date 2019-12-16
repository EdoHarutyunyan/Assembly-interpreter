#include "ExecutionManager.h"

namespace manager
{

ExecutionManager::ExecutionManager(std::vector<std::string>&& files)
	: m_interpreter(nullptr)
	, m_compiler(std::make_unique<compiler::Compiler>(std::forward<std::vector<std::string>>(files)))
{
}

void ExecutionManager::Start()
{
	//m_compiler->Start();

	m_interpreter = std::make_unique<interpreter::Interpreter>();
}

} // namespace manager
