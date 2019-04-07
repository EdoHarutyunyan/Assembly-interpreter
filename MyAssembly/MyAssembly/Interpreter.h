#pragma once
#include "VM.h"
#include "FileIO.h"

namespace interpreter
{

class Interpreter
{
public:
	Interpreter(std::string asmName);
	~Interpreter();

	void Start();

private:
	fileio::FileIO* ASM;
	virtualmachine::VM* vm;
};

}//namespace interpreter
