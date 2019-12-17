#pragma once
#include <iostream>
#include "VM.h"

namespace interpreter
{

using VMPtr = std::unique_ptr<virtualmachine::VM>;

class Interpreter
{

public:
	explicit Interpreter(/*const std::fstream& binaryFile*/);
	~Interpreter() = default;

	void Start();

private:
	VMPtr m_vm;
};

}//namespace interpreter
