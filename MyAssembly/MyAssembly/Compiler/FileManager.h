#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace parsedfile
{
class ParsedFile;
}

namespace filemanager
{

class FileManager
{
public:
	explicit FileManager(std::vector<std::string>&& paths);
	~FileManager() = default;

	std::vector<std::string> ReadFromFile(const std::string& path);
	void WriteToFile(const std::string& path, const std::vector<std::string>& lines);

	void Loader(const std::string& path, const parsedfile::ParsedFile& parsedResult);

	void ToBynary(const parsedfile::ParsedFile& parsedResult);

	std::vector<std::string> GetPaths() const;
	std::string GetBynaryFilePath() const;

private:
	std::vector<std::string> m_paths;
	std::vector<std::fstream> m_files;
	std::string m_bynaryFilePath;
	std::fstream m_bynaryFile;
};

} // namespace filemanager
