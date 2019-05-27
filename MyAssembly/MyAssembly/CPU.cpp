#include "CPU.h"
#include "Command.h"
#include "CommandNode.h"
#include "decl.h"

#include <cassert>
#include <cmath>

CPU::CPU()
	: m_ip{}
	, m_CPUdataRegisters{}
	, m_CPUaddressRegisters{}
	, m_CPUstatusRegisters{}
{
}

void CPU::add(const CommandNode& comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		byte temp = *b1;
		*b1 += *b2;
		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		word temp = *w1;
		*w1 += *w2;
		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		dword temp = *dw1;
		*dw1 += *dw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		*qw1 += *qw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
	}
}

void CPU::sub(const CommandNode & comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		byte temp = *b1;
		*b1 -= *b2;
		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		word temp = *w1;
		*w1 -= *w2;
		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		dword temp = *dw1;
		*dw1 -= *dw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		*qw1 -= *qw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
	}
}

void CPU::mul(const CommandNode & comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		byte temp = *b1;
		*b1 *= *b2;
		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		word temp = *w1;
		*w1 *= *w2;
		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		dword temp = *dw1;
		*dw1 *= *dw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		*qw1 *= *qw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
	}
}

void CPU::div(const CommandNode & comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		byte temp = *b1;
		*b1 /= *b2;
		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		word temp = *w1;
		*w1 /= *w2;
		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		dword temp = *dw1;
		*dw1 /= *dw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		*qw1 /= *qw2;
		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
	}
}

void CPU::cmp(const CommandNode & comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		byte temp = *b1 - *b2;
		m_CPUstatusRegisters.sFlag[ZF] = (temp == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 > temp || temp < *b2);
		m_CPUstatusRegisters.sFlag[SF] = (temp < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((*b1 < 0 && *b2 < 0 && temp > 0) || (*b1 > 0 && *b2 > 0 && temp < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		byte temp = *w1 - *w2;
		m_CPUstatusRegisters.sFlag[ZF] = (temp == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 > temp || temp < *w2);
		m_CPUstatusRegisters.sFlag[SF] = (temp < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((*w1 < 0 && *w2 < 0 && temp > 0) || (*w1 > 0 && *w2 > 0 && temp < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		byte temp = *dw1 - *dw2;
		m_CPUstatusRegisters.sFlag[ZF] = (temp == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 > temp || temp < *dw2);
		m_CPUstatusRegisters.sFlag[SF] = (temp < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((*dw1 < 0 && *dw2 < 0 && temp > 0) || (*dw1 > 0 && *dw2 > 0 && temp < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		byte temp = *qw1 - *qw2;
		m_CPUstatusRegisters.sFlag[ZF] = (temp == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 > temp || temp < *qw2);
		m_CPUstatusRegisters.sFlag[SF] = (temp < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((*qw1 < 0 && *qw2 < 0 && temp > 0) || (*qw1 > 0 && *qw2 > 0 && temp < 0));
	}
}

void CPU::deg(const CommandNode & comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte temp = *b1;
		std::pow(*b1, comNode.m_operand[1]);
		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp);
		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b1 > 0) || (temp > 0 && *b1 < 0));
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word temp = *w1;
		std::pow(*w1, comNode.m_operand[1]);
		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp);
		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w1 > 0) || (temp > 0 && *w1 < 0));
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword temp = *dw1;
		std::pow(*dw1, comNode.m_operand[1]);
		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp);
		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw1 > 0) || (temp > 0 && *dw1 < 0));
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		std::pow(*qw1, comNode.m_operand[1]);
		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp);
		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw1 > 0) || (temp > 0 && *qw1 < 0));
	}
}

void CPU::mov(const CommandNode& comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]];
		*b1 = *b2;
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2 || (comNode.m_operand[1]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		*w1 = *w2;
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4 || (comNode.m_operand[1]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		*dw1 = *dw2;
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8 || (comNode.m_operand[1]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		*qw1 = *qw2;
	}
}

void CPU::test(const CommandNode & comNode)
{

}

void CPU::print(const CommandNode& comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		std::cout << *b1 << std::endl;
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		std::cout << *w1 << std::endl;
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		std::cout << *dw1 << std::endl;
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		std::cout << *qw1 << std::endl;
	}
}

void CPU::assign(const CommandNode& comNode)
{
	if (comNode.m_opsize == "B")
	{
		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]];
		byte temp = *b1;//statusflags
		*b1 = comNode.m_operand[1];
	}
	else if (comNode.m_opsize == "W")
	{
		assert(!((comNode.m_operand[0]) % 2));

		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		word temp = *w1;//statusflags
		*w1 = comNode.m_operand[1];
	}
	else if (comNode.m_opsize == "DW")
	{
		assert(!((comNode.m_operand[0]) % 4));

		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		dword temp = *dw1;
		*dw1 = comNode.m_operand[1];
	}
	else if (comNode.m_opsize == "QW")
	{
		assert(!((comNode.m_operand[0]) % 8));

		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[0]]);
		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[comNode.m_operand[1]]);
		qword temp = *qw1;
		*qw1 = comNode.m_operand[1];
	}
}

void CPU::load(const CommandNode & comNode)
{
}

void CPU::setIp(const size_t newIp)
{
	m_ip = newIp;
}

std::vector<bool> CPU::getStFlag() const
{
	return m_CPUstatusRegisters.getFlag();
}
