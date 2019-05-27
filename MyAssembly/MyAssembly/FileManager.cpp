#include "FileManager.h"
#include "CommandNode.h"

#include <cassert>
#include <sstream>
#include <vector>

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

//std::vector<BaseCommand*> FileManager::Tokenizer(std::vector<std::string> file)
//{
//	//std::map<std::string, size_t> commandMap;
//
//	std::vector<std::string> tokens;
//
//	std::vector<BaseCommand*> com;
//	com.resize(file.size());
//	size_t comSize = 0;
//
//	command::mapInit(commandMap);
//	labelInit(file);
//
//	for (size_t i = 0; i < file.size(); ++i)
//	{
//		//split(file[i], tokens);
//
//		if (auto it = command::labelMap.find(tokens[0]);
//			!(it == command::labelMap.end()))
//		{
//			tokens.clear();
//			continue;
//		}
//
//		switch (commandMap[tokens[0]])
//		{
//		case command::eASSIGN:
//			com[comSize++] = new command::Assign{ CommandNode{ tokens[0], tokens[2], std::atoi(tokens[3].c_str()), tokens[1] } };
//			break;
//		case command::eADD:
//			com[comSize++] = new command::Add{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eSUB:
//			com[comSize++] = new command::Sub{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eMUL:
//			com[comSize++] = new command::Mul{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eDIV:
//			com[comSize++] = new command::Div{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eDEG:
//			com[comSize++] = new command::Deg{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::ePRINT:
//			com[comSize++] = new command::Print{ CommandNode{ tokens[0], tokens[2], tokens[1] } };
//			break;
//		case command::eCMP:
//			com[comSize++] = new command::Cmp{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eTEST:
//			com[comSize++] = new command::Test{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eMOV:
//			com[comSize++] = new command::Move{ CommandNode{ tokens[0], {tokens[2], tokens[3]}, tokens[1] } };
//			break;
//		case command::eJUMP:
//			com[comSize++] = new command::Jump{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJZ:
//			com[comSize++] = new command::JZ{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJNZ:
//			com[comSize++] = new command::JNZ{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJS:
//			com[comSize++] = new command::JS{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJNS:
//			com[comSize++] = new command::JNS{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJO:
//			com[comSize++] = new command::JO{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJNO:
//			com[comSize++] = new command::JNO{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJA:
//			com[comSize++] = new command::JA{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJAE:
//			com[comSize++] = new command::JAE{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJB:
//			com[comSize++] = new command::JB{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJBE:
//			com[comSize++] = new command::JBE{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJG:
//			com[comSize++] = new command::JG{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJGE:
//			com[comSize++] = new command::JGE{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJL:
//			com[comSize++] = new command::JL{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		case command::eJLE:
//			com[comSize++] = new command::JLE{ CommandNode{ tokens[0], command::labelMap[tokens[1]] } };
//			break;
//		default:
//			assert(false);
//		}
//
//		tokens.clear();
//	}
//
//	return com;
//}

//void labelInit(std::vector<std::string> file)
//{
//	std::vector<std::string> tokens;
//
//	for (size_t i = 0; i < file.size(); ++i)
//	{
//		//split(file[i], tokens);
//
//		if (char lastChar = tokens[0].at(tokens[0].length() - 1); lastChar == ':')
//		{
//			command::labelMap[tokens[0]] = i;
//		}
//
//		tokens.clear();
//	}
//}

}//namespace filemanager