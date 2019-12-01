#include "FileManager.h"

#include <iostream>

namespace filemanager
{

FileManager::FileManager(const std::string &fileName)
	: m_fileName(fileName)
	, m_bynaryFileName("BynaryFile")
	, m_file{ m_fileName, std::ifstream::in | std::ofstream::out }
	, m_bynaryFile{ m_bynaryFileName, std::ifstream::in | std::ofstream::out }
{
	if (!m_file.is_open() || !m_bynaryFile.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
	}
}

FileManager::~FileManager()
{
	m_file.close();
	m_bynaryFile.close();
}

std::vector<std::string> FileManager::ReadFromFile(const std::string& name)
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

std::string FileManager::GetFileName() const
{
	return m_fileName;
}

std::string FileManager::GetBynaryFileName() const
{
	return m_bynaryFileName;
}

}//namespace filemanager
