#pragma once

#include "VM.h"

namespace interpreter
{

class Interpreter
{
public:
	explicit Interpreter(const ParsedFile& parsingResult);
	~Interpreter();

	void Start(size_t entryPoint);

private:
	virtualmachine::VM* vm;
};

}//namespace interpreter
