#pragma once

#include <vector>
#include <string>
#include <fstream>

class BaseCommand;

namespace filemanager
{

class FileManager
{
public:
	FileManager(const std::string& file_name);

	~FileManager();

	std::vector<std::string> ReadFromFile();

	void WriteToFile(const std::vector<std::string> &lines);

	//std::vector<BaseCommand*> Tokenizer(std::vector<std::string> file);

private:
	std::fstream m_file;
};

//void labelInit(std::vector<std::string> file);

}//namespace filemanager
