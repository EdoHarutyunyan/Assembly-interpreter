#pragma once
#include "Command.h"
#include "Registers.h"

namespace command
{

class Add : public Command
{
public:
	Add(const std::string firstReg, const std::string secondReg);
	~Add() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_firstReg;
	const std::string m_secondReg;
};

class Sub : public Command
{
public:
	Sub(const std::string firstReg, const std::string secondReg);
	~Sub() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_firstReg;
	const std::string m_secondReg;
};

class Mul : public Command
{
public:
	Mul(const std::string firstReg, const std::string secondReg);
	~Mul() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_firstReg;
	const std::string m_secondReg;
};

class Div : public Command
{
public:
	Div(const std::string firstReg, const std::string secondReg);
	~Div() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_firstReg;
	const std::string m_secondReg;
};

class Deg : public Command
{
public:
	Deg(const std::string firstReg, const std::string secondReg);
	~Deg() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_firstReg;
	const std::string m_secondReg;
};

class Assign : public Command
{
public:
	Assign(const std::string reg, const int value);
	~Assign() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_reg;
	const int m_value;
};

class Print : public Command
{
public:
	Print(const std::string regIndex);
	~Print() override {}
	void Execute(Registers& registers) override;
private:
	const std::string m_regIndex;
};

class Jump : public Command
{
public:
	Jump(const size_t regIndex);
	~Jump() override {}
	void Execute(Registers& registers) override;
private:
	const size_t m_line;
};

enum commandKeys { eASSIGN, eADD, eSUB, eMUL, eDIV, eDEG, ePRINT, eJUMP };
void mapInit(std::map<std::string, size_t>& comMap);

}//namespace command
