#pragma once

#include "Command.h"

namespace code
{

class Code
{
public:
	Code(std::vector<std::string> tokens, std::string extension = "DW");
	~Code() = default;

private:
	size_t m_extension;
	size_t m_lOper;
	size_t m_rOper;
};

enum Extensions;
enum Registers;

extern const size_t addressRegsStartPos;

}//namespace code
