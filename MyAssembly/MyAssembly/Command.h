#pragma once
#include "BaseCommand.h"
#include <map>
#include "CommandNode.h"

namespace command
{

class Add final : public BaseCommand
{
public:
	Add(CommandNode comNode);
	~Add() override = default;

	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Sub final : public BaseCommand
{
public:
	Sub(CommandNode comNode);
	~Sub() override = default;

	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Mul final : public BaseCommand
{
public:
	Mul(CommandNode comNode);
	~Mul() override = default;

	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Div final : public BaseCommand
{
public:
	Div(CommandNode comNode);
	~Div() override = default;

	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Deg final : public BaseCommand
{
public:
	Deg(CommandNode comNode);
	~Deg() override = default;

	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Assign final : public BaseCommand
{
public:
	Assign(CommandNode comNode);
	~Assign() override = default;
	void Execute(CPU& cpu) const override;

private:
	CommandNode m_comNode;
};

class Print : public BaseCommand
{
public:
	Print(CommandNode comNode);
	~Print() override = default;
	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class Cmp : public BaseCommand
{
public:
	Cmp(CommandNode comNode);
	~Cmp() override = default;
	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;

}; 

class Test : public BaseCommand
{
public:
	Test(CommandNode comNode);
	~Test() override = default;
	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;

};

class Move : public BaseCommand
{
public:
	Move(CommandNode comNode);
	~Move() override = default;
	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;

};

//class Load : public BaseCommand
//{
//public:
//	Load(CommandNode comNode);
//	~Load() override = default;
//	void Execute(CPU& cpu) const override;
//private:
//	CommandNode m_comNode;
//
//};
//
//class Store : public BaseCommand
//{
//public:
//	Store(CommandNode comNode);
//	~Store() override = default;
//	void Execute(CPU& cpu) const override;
//private:
//	CommandNode m_comNode;
//
//};

class Jump : public BaseCommand
{
public:
	Jump(CommandNode comNode);
	~Jump() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JZ : public BaseCommand
{
public:
	JZ(CommandNode comNode);
	~JZ() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JNZ : public BaseCommand
{
public:
	JNZ(CommandNode comNode);
	~JNZ() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JS : public BaseCommand
{
public:
	JS(CommandNode comNode);
	~JS() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JNS : public BaseCommand
{
public:
	JNS(CommandNode comNode);
	~JNS() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};


class JO : public BaseCommand
{
public:
	JO(CommandNode comNode);
	~JO() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JNO : public BaseCommand
{
public:
	JNO(CommandNode comNode);
	~JNO() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};
class JA : public BaseCommand
{
public:
	JA(CommandNode comNode);
	~JA() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JAE : public BaseCommand
{
public:
	JAE(CommandNode comNode);
	~JAE() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JB : public BaseCommand
{
public:
	JB(CommandNode comNode);
	~JB() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JBE : public BaseCommand
{
public:
	JBE(CommandNode comNode);
	~JBE() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JG : public BaseCommand
{
public:
	JG(CommandNode comNode);
	~JG() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JGE : public BaseCommand
{
public:
	JGE(CommandNode comNode);
	~JGE() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JL : public BaseCommand
{
public:
	JL(CommandNode comNode);
	~JL() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

class JLE : public BaseCommand
{
public:
	JLE(CommandNode comNode);
	~JLE() override = default;

	void Execute(CPU& cpu) const override;
private:
	CommandNode m_comNode;
};

enum commandKeys 
{
	eASSIGN = 0,
	eADD,
	eSUB,
	eMUL,
	eDIV,
	eDEG,
	ePRINT,
	eCMP,
	eTEST,
	eMOV, 
	eJUMP,
	eJZ,
	eJNZ,
	eJS,
	eJNS,
	eJO,
	eJNO, 
	eJA, 
	eJAE, 
	eJB, 
	eJBE,
	eJG,
	eJGE,
	eJL,
	eJLE
};

void mapInit(std::map<std::string, size_t>& comMap);

extern std::map<std::string, size_t> labelMap;

}//namespace command
