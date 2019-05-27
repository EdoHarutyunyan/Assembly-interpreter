#pragma once

#include <vector>

namespace memory
{

class Memory
{
public:
	Memory();
	~Memory();

private:
	std::vector<int64_t> m_RAM;
};

}//namespace memory
