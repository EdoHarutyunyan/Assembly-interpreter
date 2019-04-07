#include "Command.h"
#include "CPU.h"

#include <iostream>
#include <cassert>
#include <map>

namespace command
{

void mapInit(std::map<std::string, size_t>& comMap)
{
	comMap["ASSIGN"] = eASSIGN;
	comMap["ADD"]	 = eADD;
	comMap["SUB"]	 = eSUB;
	comMap["MUL"]	 = eMUL;
	comMap["DIV"]	 = eDIV;
	comMap["DEG"]	 = eDEG;
	comMap["PRINT"]  = ePRINT;
	comMap["CMP"]	 = eCMP;
	comMap["TEST"]   = eTEST;
	comMap["MOV"]    = eMOV;
	comMap["JUMP"]   = eJUMP;
	comMap["JZ"]	 = eJZ;
	comMap["JNZ"]    = eJNZ;
	comMap["JS"]	 = eJS;
	comMap["JNS"]	 = eJNS;
	comMap["JO"]     = eJO;
	comMap["JNO"]    = eJNO;
	comMap["JA"]	 = eJA;
	comMap["JAE"]	 = eJAE;
	comMap["JB"]	 = eJB;
	comMap["JBE"]	 = eJBE;
	comMap["JG"]	 = eJG;
	comMap["JGE"]	 = eJGE;
	comMap["JL"]	 = eJL;
	comMap["JLE"]	 = eJLE;
}

std::map<std::string, size_t> labelMap;

Add::Add(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Add::Execute(CPU& cpu) const
{
	cpu.add(m_comNode);
}

Print::Print(CommandNode comNode)
	: m_comNode{comNode}
{
}

void Print::Execute(CPU& cpu) const
{
	cpu.print(m_comNode);
}

Sub::Sub(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Sub::Execute(CPU& cpu) const
{
	cpu.sub(m_comNode);
}

Mul::Mul(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Mul::Execute(CPU & cpu) const
{
	cpu.mul(m_comNode);
}

Div::Div(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Div::Execute(CPU & cpu) const
{
	cpu.div(m_comNode);
}

Deg::Deg(CommandNode comNode)
	: m_comNode{comNode}
{
}

void Deg::Execute(CPU & cpu) const
{
	cpu.deg(m_comNode);
}

Assign::Assign(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Assign::Execute(CPU& cpu) const
{
	cpu.assign(m_comNode);
}

Cmp::Cmp(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Cmp::Execute(CPU & cpu) const
{
	cpu.cmp(m_comNode);
}

Test::Test(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Test::Execute(CPU & cpu) const
{
	cpu.test(m_comNode);
}

Move::Move(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Move::Execute(CPU & cpu) const
{
	cpu.mov(m_comNode);
}

//Load::Load(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}
//
//Store::Store(CommandNode comNode)
//	: m_comNode{ comNode }
//{
//}

Jump::Jump(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void Jump::Execute(CPU& cpu) const
{
	cpu.setIp(m_comNode.m_operand[0] - 1);
}


JZ::JZ(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JZ::Execute(CPU& cpu) const
{
	if (cpu.getStFlag()[ZF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JNZ::JNZ(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JNZ::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[ZF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JS::JS(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JS::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[SF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JNS::JNS(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JNS::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[SF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JA::JA(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JA::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[CF] && !cpu.getStFlag()[ZF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JAE::JAE(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JAE::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[CF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JB::JB(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JB::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[CF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JBE::JBE(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JBE::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[CF] && cpu.getStFlag()[ZF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JG::JG(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JG::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[ZF] && (cpu.getStFlag()[SF] == cpu.getStFlag()[OF]))
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JGE::JGE(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JGE::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[SF] == cpu.getStFlag()[OF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JL::JL(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JL::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[SF] != cpu.getStFlag()[OF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JLE::JLE(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JLE::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[ZF] && (cpu.getStFlag()[SF] != cpu.getStFlag()[OF]))
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JO::JO(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JO::Execute(CPU & cpu) const
{
	if (cpu.getStFlag()[OF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

JNO::JNO(CommandNode comNode)
	: m_comNode{ comNode }
{
}

void JNO::Execute(CPU & cpu) const
{
	if (!cpu.getStFlag()[OF])
	{
		cpu.setIp(m_comNode.m_operand[0] - 1);
	}
}

}//namespace command
