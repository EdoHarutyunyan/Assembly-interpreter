#include <iostream>
#include "Interpreter.h"

int main()
{
	interpreter::Interpreter pc("assembly.txt");
	pc.Start();

	system("pause");
	return 0;
}