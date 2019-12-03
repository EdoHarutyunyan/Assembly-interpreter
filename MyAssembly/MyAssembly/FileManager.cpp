#include "FileManager.h"
#include "ParsedFile.h"

#include <iostream>
#include <bitset>

namespace filemanager
{

FileManager::FileManager(const std::string &fileName)
	: m_fileName(fileName)
	, m_bynaryFileName("BynaryFile.txt")
{
}

std::vector<std::string> FileManager::ReadFromFile(const std::string& name)
{
	std::ifstream fin(name);
	std::vector<std::string> file;
	std::string line;

	if (!fin.is_open())
	{
		std::cerr << "FileManager::ReadFromFile(): Problem during open " << name << " file." << std::endl;
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
		std::cerr << "FileManager::WriteToFile(): Problem during open " << name << " file." << std::endl;
	}

	for (const auto &line : lines)
	{
		fout << line << std::endl;
	}

	fout.close();
}

void FileManager::ToBynary(const ParsedFile& parsedResult)
{
	std::vector<std::string> bynaryVector;
	
	const size_t endOfDataSegment = 2 + parsedResult.m_dataStorage.size();
	bynaryVector.push_back(std::bitset<32>(endOfDataSegment).to_string()); // header of BynaryFile
	bynaryVector.push_back(std::bitset<32>(parsedResult.m_stackSize).to_string());

	for (const auto& data : parsedResult.m_dataStorage)
	{
		bynaryVector.push_back(std::bitset<32>(data).to_string());
	}

	bynaryVector.push_back(std::bitset<32>(parsedResult.m_entryPoint).to_string());

	WriteToFile(GetBynaryFileName(), bynaryVector);
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
