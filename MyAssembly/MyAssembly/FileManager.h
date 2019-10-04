#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace filemanager
{

class FileManager
{
public:
	explicit FileManager(const std::string& file_name);

	~FileManager();

	std::vector<std::string> ReadFromFile();

	void WriteToFile(const std::vector<std::string>& lines);

private:
	std::fstream m_file;
};

}//namespace filemanager
