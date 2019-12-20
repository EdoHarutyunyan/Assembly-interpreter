#pragma once

#include "Command.h"

#include <unordered_map>
#include <iostream>

namespace code
{

namespace arg
{
	
enum class Type : uint8_t
{
	FromMemory = 0,
	FromAddressRegister = 1,
	FromGeneralPorposeRegister = 2
};

class Arg
{
public:
	Arg() = default;
	Arg(const std::string& arg);
	
	~Arg() = default;

public:
	Type m_type;
	uint8_t m_operand;
};

} // namespace arg

using ArgPtr = std::unique_ptr<arg::Arg>;

class Code
{
public:
	explicit Code(size_t opcode);
	Code(size_t opcode, const std::string& reg);
	~Code() = default;

	void SourceCodeGenerator(
		const std::vector<std::string>& tokens,
		std::unordered_map<std::string, size_t>& funcDefinition,
		size_t indexOfParsingFile);

	bool SetExtension(const std::string& extension);
	void SetLeftArg(const std::string& arg);
	void SetLeftArg(const std::string& leftArg, std::map<std::string, size_t>& labels);
	void SetRightArg(const std::string& rOp,
		std::unordered_map<std::string, size_t>& funcDefinition,
		size_t indexOfParsingFile);
	
	void SetRightArg(size_t index);
	void SetLeftArg(size_t index);

	size_t GetOpcode() const;
	size_t GetExtension() const;
	arg::Arg GetLeftArg() const;
	arg::Arg GetRightArg() const;

	static std::unordered_map<std::string, size_t> extensionTable;

private:
	size_t m_opcode;
	size_t m_extension;
	ArgPtr m_leftArg;
	ArgPtr m_rightArg;
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

enum GeneralPurposeRegisters
{
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
	R31,
	R32,
	R33,
	R34,
	R35,
	R36,
	R37,
	R38,
	R39,
	R40,
	R41,
	R42,
	R43,
	R44,
	R45,
	R46,
	R47,
	R48,
	R49,
	R50,
	R51,
	R52,
	R53,
	R54,
	R55,
	R56,
	R57,
	R58,
	R59,
	R60,
	R61,
	R62,
	R63
};

enum AddressRegisters
{
	A0 = 0,
	A1 = 1,
	A2 = 2,
	A3 = 3,
	A4 = 4,
	A5 = 5,
	A6 = 6,
	A7 = 7
};

} // namespace code
