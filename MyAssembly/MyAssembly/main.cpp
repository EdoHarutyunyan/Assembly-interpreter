#include <iostream>
#include "ExecutionManager.h"

int main()
try
{
	manager::ExecutionManager em("assembly.txt");
	em.Start();

	system("pause");
	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
	system("pause");
}