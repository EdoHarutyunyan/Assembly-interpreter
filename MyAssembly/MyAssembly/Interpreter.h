#pragma once

#include "VM.h"
#include "FileManager.h"
//#include "Code.h"

namespace interpreter
{

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	void Start();

private:
	virtualmachine::VM* vm;
	//std::vector<code::Code> dataStructure;
};

}//namespace interpreter
