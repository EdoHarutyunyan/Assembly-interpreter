#pragma once

#include "Code.h"
#include "DataRegisters.h"
#include "StatusRegisters.h"
#include "AddressRegisters.h"
#include "Memory.h"

#include <vector>

class CPU
{
public:
	explicit CPU(memory::Memory* mem);
	~CPU() = default;

	void Execute(size_t entryPoint, std::vector<code::Code> m_instruction);

	bool CheckCC(size_t extension);

	void assign(size_t extension, size_t lOper, size_t rOper);
	void add(size_t extension, size_t lOper, size_t rOper);
	void sub(size_t extension, size_t lOper, size_t rOper);
	void mul(size_t extension, size_t lOper, size_t rOper);
	void div(size_t extension, size_t lOper, size_t rOper);
	void cmp(size_t extension, size_t lOper, size_t rOper);
	void mov(size_t extension, size_t lOper, size_t rOper);
	void test(size_t extension, size_t lOper, size_t rOper);


	void print();
	void load(size_t extension, size_t lOper, size_t rOper);
	void store(size_t extension, size_t lOper, size_t rOper);

	void setIp(const size_t newIp);

	std::vector<bool> getStFlag() const;

	size_t m_ip;

private:
	DataRegisters m_CPUdataRegisters;
	StatusRegisters m_CPUstatusRegisters;
	AddressRegisters m_CPUaddressRegisters;

	memory::Memory* m_memory;
};
