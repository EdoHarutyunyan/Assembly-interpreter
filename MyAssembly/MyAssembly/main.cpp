#include <iostream>
#include "ExecutionManager.h"

int main()
try
{
	std::vector<std::string> paths{ "assembly.txt", "assembly2.txt", "assembly3.txt" };
	manager::ExecutionManager em(std::move(paths));
	em.Start();

	system("pause");
	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
	system("pause");
}
