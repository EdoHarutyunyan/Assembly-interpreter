//#include "CPU.h"
//#include "decl.h"
//#include "Command.h"
//
//#include <cassert>
//#include <cmath>
//
//CPU::CPU(memory::Memory* mem)
//	: m_ip{}
//	, m_CPUdataRegisters{}
//	, m_CPUaddressRegisters{}
//	, m_CPUstatusRegisters{}
//	, m_memory{mem}
//{
//}
//
//void CPU::Execute(const size_t entryPoint, std::vector<code::Code> instruction)
//{
//	using namespace command;
//
//	while(true)
//	{
//		switch (instruction[m_ip].GetOpcode())
//		{
//		case commandKeys::eASSIGN:
//		{
//			assign(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eADD:
//		{
//			add(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eSUB:
//		{
//			sub(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eMUL:
//		{
//			mul(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eDIV:
//		{
//			div(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eSTORE:
//		{
//			store(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eLOAD:
//		{
//			load(instruction[m_ip].GetExtension(), instruction[m_ip].GetlOper(), instruction[m_ip].GetrOper());
//			break;
//		}
//		case commandKeys::eEND:
//		{
//			return;
//		}
//
//		default:
//			break;
//		}
//		++m_ip;
//	}
//}
//
//bool CPU::CheckCC(const size_t extension)
//{
//	switch (extension)
//	{
//	case code::Extensions::xE:
//	{
//		return getStFlag()[ZF];
//	}
//	case code::Extensions::xNE:
//	{
//		return !getStFlag()[ZF];
//	}
//	case code::Extensions::xA:
//	{
//		return (getStFlag()[CF] && !getStFlag()[ZF]);
//	}
//	case code::Extensions::xAE:
//	{
//		return !getStFlag()[CF];
//	}
//	case code::Extensions::xB:
//	{
//		return getStFlag()[CF];
//	}
//	case code::Extensions::xBE:
//	{
//		return (getStFlag()[CF] && getStFlag()[ZF]);
//	}
//	case code::Extensions::xG:
//	{
//		return (!getStFlag()[ZF] &&(getStFlag()[CF] == getStFlag()[OF]));
//	}
//	case code::Extensions::xGE:
//	{
//		return (getStFlag()[CF] == getStFlag()[OF]);
//	}
//	case code::Extensions::xL:
//	{
//		return (getStFlag()[SF] != getStFlag()[OF]);
//	}
//	case code::Extensions::xLE:
//	{
//		return ((getStFlag()[SF] != getStFlag()[OF]) && getStFlag()[ZF]);
//	}
//	case code::Extensions::xO:
//	{
//		return getStFlag()[OF];
//	}
//	case code::Extensions::xNO:
//	{
//		return !getStFlag()[OF];
//	}
//	case code::Extensions::xS:
//	{
//		return getStFlag()[SF];
//	}
//	case code::Extensions::xNS:
//	{
//		return !getStFlag()[SF];
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void CPU::add(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 += *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//
//		return;
//	}
//
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[lOper];
//		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[rOper];
//		byte temp = *b1;
//		*b1 += *b2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
//		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!(lOper % 2 || rOper % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		word temp = *w1;
//		*w1 += *w2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
//		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 += *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!(lOper % 8 || rOper % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		qword temp = *qw1;
//		*qw1 += *qw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
//		break;
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//
//void CPU::sub(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 -= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//
//		return;
//	}
//
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[lOper];
//		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[rOper];
//		byte temp = *b1;
//		*b1 -= *b2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
//		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!(lOper % 2 || rOper % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		word temp = *w1;
//		*w1 -= *w2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
//		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 -= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!(lOper % 8 || rOper % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		qword temp = *qw1;
//		*qw1 -= *qw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
//		break;
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void CPU::mul(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 *= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//
//		return;
//	}
//
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[lOper];
//		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[rOper];
//		byte temp = *b1;
//		*b1 *= *b2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
//		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!(lOper % 2 || rOper % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		word temp = *w1;
//		*w1 *= *w2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
//		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 *= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!(lOper % 8 || rOper % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		qword temp = *qw1;
//		*qw1 *= *qw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
//		break;
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void CPU::div(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 /= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//
//		return;
//	}
//
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b1 = &m_CPUdataRegisters.m_dataRegisters[lOper];
//		byte* b2 = &m_CPUdataRegisters.m_dataRegisters[rOper];
//		byte temp = *b1;
//		*b1 /= *b2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*b1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*b1 < temp || *b1 < *b2);
//		m_CPUstatusRegisters.sFlag[SF] = (*b1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *b2 < 0 && *b1 > 0) || (temp > 0 && *b2 > 0 && *b1 < 0));
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!(lOper % 2 || rOper % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		word* w2 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		word temp = *w1;
//		*w1 /= *w2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*w1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*w1 < temp || *w1 < *w2);
//		m_CPUstatusRegisters.sFlag[SF] = (*w1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *w2 < 0 && *w1 > 0) || (temp > 0 && *w2 > 0 && *w1 < 0));
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		dword* dw2 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		dword temp = *dw1;
//		*dw1 /= *dw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*dw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*dw1 < temp || *dw1 < *dw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*dw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *dw2 < 0 && *dw1 > 0) || (temp > 0 && *dw2 > 0 && *dw1 < 0));
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!(lOper % 8 || rOper % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//		qword* qw2 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[rOper]);
//		qword temp = *qw1;
//		*qw1 /= *qw2;
//		m_CPUstatusRegisters.sFlag[ZF] = (*qw1 == 0);
//		m_CPUstatusRegisters.sFlag[CF] = (*qw1 < temp || *qw1 < *qw2);
//		m_CPUstatusRegisters.sFlag[SF] = (*qw1 < 0);
//		m_CPUstatusRegisters.sFlag[OF] = ((temp < 0 && *qw2 < 0 && *qw1 > 0) || (temp > 0 && *qw2 > 0 && *qw1 < 0));
//
//		break;
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void CPU::assign(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUaddressRegisters.aReg[lOper - code::addressRegsStartPos]);
//		*dw1 = rOper;
//
//		return;
//	}
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b1 = &m_CPUaddressRegisters.aReg[lOper - code::addressRegsStartPos];
//		*b1 = rOper;
//
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!(lOper % 2 || rOper % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUaddressRegisters.aReg[lOper - code::addressRegsStartPos]);
//		*w1 = rOper;
//		
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		assert(!(lOper % 4 || rOper % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUaddressRegisters.aReg[lOper - code::addressRegsStartPos]);
//		*dw1 = rOper;
//		
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!(lOper % 8 || rOper % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper - code::addressRegsStartPos]);
//		*qw1 = rOper;
//
//		break;
//	}
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void CPU::load(const size_t extension, const size_t lOper, const size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		*dw1 = m_memory->getRAM()[m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize()];
//
//		return;
//	}
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b = &m_CPUdataRegisters.m_dataRegisters[lOper];
//
//		*b = m_memory->getRAM()[m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize()];
//
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!((lOper) % 2 || (rOper) % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		*w1 = m_memory->getRAM()[m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize()];
//
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		*dw1 = m_memory->getRAM()[m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize()];
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!((lOper) % 8 || (rOper) % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		*qw1 = m_memory->getRAM()[m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize()];
//		break;
//	}
//	default:
//		break;
//	}
//}
//
//void CPU::store(size_t extension, size_t lOper, size_t rOper)
//{
//	if (extension >= code::Extensions::xE && extension <= code::Extensions::xNS)
//	{
//		if (!CheckCC(extension))
//		{
//			return;
//		}
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		m_memory->setRAM(m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize(), *dw1);
//
//		return;
//	}
//	switch (extension)
//	{
//	case code::Extensions::BYTE:
//	{
//		byte* b = &m_CPUdataRegisters.m_dataRegisters[lOper];
//
//		m_memory->setRAM(m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize(), *b);
//
//		break;
//	}
//	case code::Extensions::WORD:
//	{
//		assert(!((lOper) % 2 || (rOper) % 2));
//
//		word* w1 = reinterpret_cast<word*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		m_memory->setRAM(m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize(), *w1);
//		
//		break;
//	}
//	case code::Extensions::DWORD:
//	{
//		assert(!((lOper) % 4 || (rOper) % 4));
//
//		dword* dw1 = reinterpret_cast<dword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		m_memory->setRAM(m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize(), *dw1);
//
//		break;
//	}
//	case code::Extensions::QWORD:
//	{
//		assert(!((lOper) % 8 || (rOper) % 8));
//
//		qword* qw1 = reinterpret_cast<qword*>(&m_CPUdataRegisters.m_dataRegisters[lOper]);
//
//		m_memory->setRAM(m_CPUaddressRegisters.aReg[rOper - code::addressRegsStartPos] + m_memory->getStackSize(), *qw1);
//
//		break;
//	}
//	default:
//		break;
//	}
//}
//
//void CPU::setIp(const size_t newIp)
//{
//	m_ip = newIp;
//}
//
//std::vector<bool> CPU::getStFlag() const
//{
//	return m_CPUstatusRegisters.getFlag();
//}
