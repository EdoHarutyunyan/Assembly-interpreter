#include "FileManager.h"

#include <iostream>

namespace filemanager
{

FileManager::FileManager(const std::string &file_name)
	: m_file{file_name, std::ifstream::in | std::ofstream::out}
{
	if (!m_file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
	}
}

FileManager::~FileManager()
{
	m_file.close();
}

std::vector<std::string> FileManager::ReadFromFile()
{
	std::vector<std::string> file;
	std::string line;

	while (getline(m_file, line))
	{
		file.push_back(line);
	}

	return file;
}

void FileManager::WriteToFile(const std::vector<std::string>& lines)
{
	for (const auto &line : lines)
	{
		m_file << line << std::endl;
	}
}

}//namespace filemanager
