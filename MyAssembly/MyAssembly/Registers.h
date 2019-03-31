#pragma once
#include <vector>
#include <map>

struct Registers
{
	Registers();
	std::map<std::string, size_t> m_registers;
	size_t m_IP;
};

enum regKeys { R1, R2, R3, R4 };
