#include <iostream>
#include "Compiler.h"
#include "Interpreter.h"

int main()
try
{
	compiler::Compiler comp("assembly.txt");
	comp.Start();
	comp.print();
	/*interpreter::Interpreter pc("assembly.txt");
	pc.Start();*/

	system("pause");
	return 0;
}
catch (const std::exception& e)
{
	e.what();
	system("pause");
}