#pragma once

#include "Command.h"

#include <unordered_map>
#include <set>

namespace code
{

class Code
{
public:
	explicit Code(size_t opcode);
	Code(size_t opcode, std::string reg);
	~Code() = default;

	void SourceCodeGenerator(
		const std::vector<std::string>& tokens,
		std::set<std::string>& funcDeclaration,
		std::unordered_map<std::string, size_t>& funcDefinition);

	bool setExtension(const std::string& ext);
	void setlOper(const std::string& reg);
	void setlOper(const std::string& lOper, std::map<std::string, size_t>& labels);
	void setrOper(const std::string& rOp, std::set<std::string>& funcDeclaration,
		std::unordered_map<std::string, size_t>& funcDefinition);
	
	void setrOper(size_t index);
	void setlOper(size_t index);

	size_t getOpcode()const;
	size_t getExtension()const;
	size_t getlOper()const;
	size_t getrOper()const;

	static std::unordered_map<std::string, size_t> extTable;

private:
	size_t regInit(const std::string& reg);

private:
	size_t m_opcode;
	size_t m_extension;
	size_t m_lOper;
	size_t m_rOper;

};

enum Extensions
{
	// CC
	xE = 1,
	xNE = 2,
	xA = 3,
	xAE = 4,
	xB = 5,
	xBE = 6,
	xG = 7,
	xGE = 8,
	xL = 9,
	xLE = 10,
	xO = 11,
	xNO = 12,
	xS = 13,
	xNS = 14,

	// Opsize
	BYTE = 20,
	WORD = 21,
	DWORD = 22,
	QWORD = 23
};

enum Registers
{
	// General purpose registers
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5, 
	R6,
	R7,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	R16,
	R17,
	R18,
	R19,
	R20, 
	R21,
	R22,
	R23,
	R24,
	R25,
	R26,
	R27,
	R28,
	R29,
	R30,
	//...
	R63,

	//Address Registers
	A0 = 70,
	A1,
	A2,
	A3,
	A4,
	A5,
	A6,
	A7
};

extern const size_t addressRegsStartPos;

}//namespace code
