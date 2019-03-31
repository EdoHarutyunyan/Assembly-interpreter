#pragma once
#include "VM.h"
#include "FileIO.h"

namespace interpreter
{

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

private:
	virtualmachine::VM* vm;
	fileio::FileIO* ASM;
};

}//namespace interpreter
