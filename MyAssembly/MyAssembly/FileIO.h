#pragma once

#include <vector>
#include <string>
#include <fstream>

class BaseCommand;

namespace fileio
{

class FileIO
{
public:
	FileIO(const std::string& file_name);

	~FileIO() = default;

	std::vector<std::string> ReadFromFile();

	void WriteToFile(const std::vector<std::string> &lines);

	std::vector<BaseCommand*> Tokenizer(std::vector<std::string> file);

private:
	std::string m_fileName;
};

void split(const std::string& line, std::vector<std::string>& res);
void labelInit(std::vector<std::string> file);

}//namespace fileio
