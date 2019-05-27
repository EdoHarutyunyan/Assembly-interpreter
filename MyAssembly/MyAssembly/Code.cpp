#include "Code.h"
#include "Type.h"

#include <sstream>

namespace code
{

Code::Code(std::vector<std::string> tokens, std::string extension = "DW")
{
}

const size_t addressRegsStartPos = 70;

enum Extensions
{
	// CC
	xE  = 1,
	xNE	= 2,
	xA	= 3,
	xAE	= 4,
	xB	= 5,
	xBE	= 6,
	xG	= 7,
	xGE	= 8,
	xL	= 9,
	xLE	= 10,
	xO	= 11,
	xNO	= 12,
	xS	= 13,
	xNS	= 14,

	// Opsize
	BYTE  = 20,
	WORD  = 21,
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

}//namespace code