#include "Memory.h"

namespace memory
{

Memory::Memory(const size_t stackSize, const std::vector<byte>& data)
	: m_size{data.size() + stackSize}
	, m_stackSize{stackSize}
{
	m_RAM.resize(m_size);

	for (size_t i = stackSize; i < m_RAM.size(); ++i)
	{
		m_RAM[i] = data[i - stackSize];
	}
}

std::vector<byte> Memory::getRAM() const
{
	return m_RAM;
}

void Memory::setRAM(const size_t index, const byte data)
{
	m_RAM[index] = data;
}

size_t Memory::getStackSize() const
{
	return m_stackSize;
}

Memory::~Memory()
{
}

}//namespace memory
