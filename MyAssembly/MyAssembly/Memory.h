#pragma once
#include "decl.h"

#include <vector>

namespace memory
{

class Memory
{
public:
	Memory(size_t stackSize, const std::vector<byte>& data);
	~Memory();

	std::vector<byte> getRAM() const; // load
	void setRAM(size_t index, byte data); // store
	size_t getStackSize() const;


private:
	std::vector<byte> m_RAM;
	size_t m_stackSize;
	size_t m_size;
};

}//namespace memory
