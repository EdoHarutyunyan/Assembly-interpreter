#pragma once
#include "Commands.h"
#include "Registers.h"
#include <vector>

namespace cpu
{

class CPU
{
public:
	CPU();
	~CPU();

	std::vector<Command*> Tokenizer(std::vector<std::string> file);

private:
	Registers m_CPUregisters;
	std::vector<Command*> m_commands;
};

void split(const std::string& line, std::vector<std::string>& res);

}//namespace cpu
