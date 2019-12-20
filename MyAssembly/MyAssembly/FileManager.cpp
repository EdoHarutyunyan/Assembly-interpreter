#include "FileManager.h"
#include "ParsedFile.h"
#include <iostream>

namespace filemanager
{

FileManager::FileManager(std::vector<std::string>&& paths)
	: m_paths(std::forward<std::vector<std::string>>(paths))
	, m_bynaryFilePath("BynaryFile.bin")
{
}

std::vector<std::string> FileManager::ReadFromFile(const std::string& path)
{
	std::ifstream fin(path, std::ifstream::in);
	std::vector<std::string> file;
	std::string line;

	if (!fin.is_open())
	{
		std::cerr << "FileManager::ReadFromFile(): Problem during open " << path << " file." << std::endl;
	}

	while (getline(fin, line))
	{
		file.push_back(line);
	}

	fin.close();
	return file;
}

void FileManager::WriteToFile(const std::string& path, const std::vector<std::string>& lines)
{
	std::ofstream fout(path);
	
	if (!fout.is_open())
	{
		std::cerr << "FileManager::WriteToFile(): Problem during open " << path << " file." << std::endl;
	}

	for (const auto &line : lines)
	{
		fout << line << std::endl;
	}

	fout.close();
}

void FileManager::ToBynary(const parsedfile::ParsedFile& parsedResult)
{
	//WriteToFile(GetBynaryFileName(), bynaryVector);
}

std::vector<std::string> FileManager::GetPaths() const
{
	return m_paths;
}

std::string FileManager::GetBynaryFilePath() const
{
	return m_bynaryFilePath;
}
} // namespace filemanager
