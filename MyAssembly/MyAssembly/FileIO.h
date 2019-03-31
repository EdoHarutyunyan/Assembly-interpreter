#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace fileio
{

class FileIO
{
public:
	FileIO(const std::string &file_name);

	~FileIO();

	std::vector<std::string> ReadFromFile();

	void WriteToFile(const std::vector<std::string> &lines);

private:
	std::fstream assembly;
};

}//namespace fileio
