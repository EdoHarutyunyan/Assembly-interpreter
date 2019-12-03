#pragma once

#include <vector>
#include <string>
#include <fstream>

class ParsedFile;

namespace filemanager
{

class FileManager
{
public:
	explicit FileManager(const std::string& fileName);
	~FileManager() = default;

	std::vector<std::string> ReadFromFile(const std::string& name);
	void WriteToFile(const std::string& name, const std::vector<std::string>& lines);
	
	void ToBynary(const ParsedFile& parsedResult);

	std::string GetFileName() const;
	std::string GetBynaryFileName() const;

private:
	std::string m_fileName;
	std::string m_bynaryFileName;
	std::fstream m_file;
	std::fstream m_bynaryFile;
};

} // namespace filemanager
