#pragma once
#include "Command.h"
#include "DataRegisters.h"
#include "StatusRegisters.h"
#include "AddressRegisters.h"

#include <vector>

class CommandNode;

class CPU
{
public:
	CPU();
	~CPU() = default;

	void add(const CommandNode& comNode);
	void sub(const CommandNode& comNode);
	void mul(const CommandNode& comNode);
	void div(const CommandNode& comNode);
	void cmp(const CommandNode& comNode);
	void deg(const CommandNode& comNode);
	void mov(const CommandNode& comNode);
	void test(const CommandNode& comNode);


	void print(const CommandNode& comNode);
	void assign(const CommandNode& comNode);
	void load(const CommandNode& comNode);
	void store(const CommandNode& comNode);

	void setIp(const size_t newIp);

	std::vector<bool> getStFlag() const;

	size_t m_ip;

private:
	DataRegisters m_CPUdataRegisters;
	StatusRegisters m_CPUstatusRegisters;
	AddressRegisters m_CPUaddressRegisters;
};
