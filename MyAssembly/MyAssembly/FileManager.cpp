#include "FileManager.h"

#include <iostream>

namespace filemanager
{

FileManager::FileManager(const std::string &fileName)
	: m_fileName(fileName)
	, m_bynaryFileName("BynaryFile")
{
}

std::vector<std::string> FileManager::ReadFromFile(const std::string& name)
{
	std::ifstream fin(name);
	std::vector<std::string> file;
	std::string line;

	if (!fin.is_open())
	{
		std::cerr << "FileManager::ReadFromFile(): Problem during open " << name << " file.";
	}

	while (getline(fin, line))
	{
		file.push_back(line);
	}

	fin.close();
	return file;
}

void FileManager::WriteToFile(const std::string& name, const std::vector<std::string>& lines)
{
	std::ofstream fout(name);
	
	if (!fout.is_open())
	{
		std::cerr << "FileManager::WriteToFile(): Problem during open " << name << " file.";
	}

	for (const auto &line : lines)
	{
		fout << line << std::endl;
	}

	fout.close();
}

void FileManager::ToBynary(const ParsedFile& parsedResult)
{
}

std::string FileManager::GetFileName() const
{
	return m_fileName;
}

std::string FileManager::GetBynaryFileName() const
{
	return m_bynaryFileName;
}

} // namespace filemanager
