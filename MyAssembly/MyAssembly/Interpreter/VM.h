#pragma once

#include "Processor.h"
#include "Memory.h"

namespace virtualmachine
{

using MemoryPtr = std::shared_ptr<memory::Memory>;
using ProcessorPtr = std::unique_ptr<processor::Processor>;

class VM
{
public:
	VM();

	~VM() = default;

	void Start();

private:
	MemoryPtr m_memory;
	ProcessorPtr m_proccessor;
};

} // namespace virtualmachine
