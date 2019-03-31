#include "FileIO.h"

namespace fileio
{

FileIO::FileIO(const std::string &file_name)
	: assembly{ file_name, std::fstream::out | std::fstream::in }
{
}


FileIO::~FileIO()
{
	assembly.close();
}

std::vector<std::string> FileIO::ReadFromFile()
{
	std::vector<std::string> result;

	assembly.seekg(0);

	if (assembly.is_open())
	{
		std::string line;
		while (getline(assembly, line))
		{
			result.push_back(line);
		}
	}

	return result;
}

void FileIO::WriteToFile(const std::vector<std::string>& lines)
{
	if (assembly.is_open())
	{
		for (const auto &line : lines)
		{
			assembly << line << std::endl;
		}
	}
}

}//namespace fileio
