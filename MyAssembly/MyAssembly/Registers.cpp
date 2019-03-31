#include "Registers.h"

Registers::Registers()
	: m_IP{}
{
	m_registers["R1"] = 1;
	m_registers["R2"] = 2;
	m_registers["R3"] = 3;
	m_registers["R4"] = 4;
}
