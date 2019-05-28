#include "Command.h"
#include "CPU.h"

#include <iostream>
#include <cassert>
#include <map>

namespace command
{

void mapInit(std::map<std::string, size_t>& comMap)
{
	comMap["NOP"]	 = eNOP;
	comMap["BREAK"]	 = eBREAK;
	comMap["END"]	 = eEND;
	comMap["JUMP"]   = eJUMP;
	comMap["CALL"]   = eCALL;
	comMap["RET"]	 = eRET;
	comMap["GFLR"]   = eGFLR;
	comMap["SFLR"]   = eSFLR;
	comMap["LOAD"]   = eLOAD;
	comMap["STORE"]  = eSTORE;
	comMap["LDREL"]  = eLDREL;
	comMap["STREL"]  = eSTREL;
	comMap["PUSHSF"] = ePUSHSF;
	comMap["POPSF"]  = ePOPSF;
	comMap["PUSHA"]  = ePUSHA;
	comMap["POP"]	 = ePOP;
	comMap["ASSIGN"] = eASSIGN;
	comMap["SET"]	 = eSET;
	comMap["MOVE"]	 = eMOVE;
	comMap["SWAP"]   = eSWAP;
	comMap["INC"]    = eINC;
	comMap["DEC"]    = eDEC;
	comMap["TEST"]   = eTEST;
	comMap["CMP"]	 = eCMP;
	comMap["IN"]     = eIN;
	comMap["OUT"]    = eOUT;
	comMap["AND"]    = eAND;
	comMap["OR"]	 = eOR;
	comMap["XOR"]	 = eXOR;
	comMap["NAND"]   = eNAND;
	comMap["NOR"]	 = eNOR;
	comMap["NOT"]	 = eNOT;
	comMap["SHL"]	 = eSHL;
	comMap["SHR"]	 = eSHR;
	comMap["ROL"]	 = eROL;
	comMap["ROR"]	 = eROR;
	comMap["SAL"]	 = eSAL;
	comMap["SAR"]	 = eSAR;
	comMap["RCL"]	 = eRCL;
	comMap["RCR"]	 = eRCR;
	comMap["ADD"]	 = eADD;
	comMap["ADC"]	 = eADC;
	comMap["SUB"]	 = eSUB;
	comMap["SBB"]	 = eSBB;
	comMap["MUL"]	 = eMUL;
	comMap["IMUL"]   = eIMUL;
	comMap["DIV"]	 = eDIV;
	comMap["IDIV"]   = eIDIV;
	comMap["NEG"]	 = eNEG;
	comMap["CAST"]	 = eCAST;
	comMap["PRINT"]  = ePRINT;
}

std::map<std::string, size_t> labelMap;

//Jump::Jump(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void Jump::Execute(CPU& cpu) const
//{
//	cpu.setIp(m_comNode.m_operand[0] - 1);
//}
//
//
//JZ::JZ(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JZ::Execute(CPU& cpu) const
//{
//	if (cpu.getStFlag()[ZF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JNZ::JNZ(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JNZ::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[ZF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JS::JS(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JS::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[SF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JNS::JNS(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JNS::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[SF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JA::JA(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JA::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[CF] && !cpu.getStFlag()[ZF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JAE::JAE(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JAE::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[CF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JB::JB(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JB::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[CF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JBE::JBE(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JBE::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[CF] && cpu.getStFlag()[ZF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JG::JG(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JG::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[ZF] && (cpu.getStFlag()[SF] == cpu.getStFlag()[OF]))
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JGE::JGE(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JGE::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[SF] == cpu.getStFlag()[OF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JL::JL(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JL::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[SF] != cpu.getStFlag()[OF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JLE::JLE(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JLE::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[ZF] && (cpu.getStFlag()[SF] != cpu.getStFlag()[OF]))
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JO::JO(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JO::Execute(CPU & cpu) const
//{
//	if (cpu.getStFlag()[OF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}
//
//JNO::JNO(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//void JNO::Execute(CPU & cpu) const
//{
//	if (!cpu.getStFlag()[OF])
//	{
//		cpu.setIp(m_comNode.m_operand[0] - 1);
//	}
//}

}//namespace command
