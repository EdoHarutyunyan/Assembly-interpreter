#include "Commands.h"
#include <iostream>
#include <map>

namespace command
{

void mapInit(std::map<std::string, size_t>& comMap)
{
	comMap["assign"] = eASSIGN;
	comMap["add"] = eADD;
	comMap["sub"] = eSUB;
	comMap["mul"] = eMUL;
	comMap["div"] = eDIV;
	comMap["print"] = ePRINT;
	comMap["jump"] = eJUMP;
}

Add::Add(const std::string firstReg, const std::string secondReg)
	: m_firstReg{ firstReg }
	, m_secondReg{ secondReg }
{
}

void Add::Execute(Registers& registers)
{
	registers.m_registers[m_firstReg] += registers.m_registers[m_secondReg];
}

Sub::Sub(const std::string firstReg, const std::string secondReg)
	: m_firstReg{ firstReg }
	, m_secondReg{ secondReg }
{
}

void Sub::Execute(Registers& registers)
{
	registers.m_registers[m_firstReg] -= registers.m_registers[m_secondReg];
}

Mul::Mul(const std::string firstReg, const std::string secondReg)
	: m_firstReg{ firstReg }
	, m_secondReg{ secondReg }
{
}

void Mul::Execute(Registers& registers)
{
	registers.m_registers[m_firstReg] *= registers.m_registers[m_secondReg];
}

Div::Div(const std::string firstReg, const std::string secondReg)
	: m_firstReg{ firstReg }
	, m_secondReg{ secondReg }
{
}

void Div::Execute(Registers& registers)
{
	registers.m_registers[m_firstReg] /= registers.m_registers[m_secondReg];
}

Deg::Deg(const std::string firstReg, const std::string secondReg)
	: m_firstReg{ firstReg }
	, m_secondReg{ secondReg }
{
}

void Deg::Execute(Registers& registers)
{
	pow(registers.m_registers[m_firstReg], registers.m_registers[m_secondReg]);
}

Assign::Assign(const std::string regIndex, const int value)
	: m_reg{ regIndex }
	, m_value{ value }
{
}

void Assign::Execute(Registers& registers)
{
	registers.m_registers[m_reg] = m_value;
}

Print::Print(const std::string regIndex)
	: m_regIndex{ regIndex }
{
}

void Print::Execute(Registers& registers)
{
	std::cout << registers.m_registers[m_regIndex] << std::endl;
}

Jump::Jump(const size_t line)
	: m_line{ line }
{
}

void Jump::Execute(Registers& registers)
{
	registers.m_IP = m_line;
}

}//namespace command