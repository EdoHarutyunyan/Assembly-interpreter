#include "CPU.h"
#include "Commands.h"

#include <fstream>
#include <cassert>
#include <map>
#include <sstream>

namespace cpu
{

CPU::CPU()
	: m_CPUregisters{}
	, m_commands{}
{
}

CPU::~CPU()
{
	for (auto com : m_commands)
	{
		delete com;
		com = nullptr;
	}
}

std::vector<Command*> CPU::Tokenizer(std::vector<std::string> file)
{
	std::string token;
	std::vector<Command*> com;
	std::map<std::string, size_t> commandMap;
	std::vector<std::string> tokens;

	command::mapInit(commandMap);

	for (size_t i = 0; i < file.size(); ++i)
	{
		split(file[i], tokens);

		switch (commandMap[tokens[0]])
		{
		case command::commandKeys::eASSIGN:
			m_commands[i] = new command::Assign(tokens[1], std::stoi(tokens[2]));
			break;
		case command::commandKeys::eADD:
			m_commands[i] = new command::Add(tokens[1], tokens[2]);
			break;
		case command::commandKeys::eSUB:
			m_commands[i] = new command::Add(tokens[1], tokens[2]);
			break;
		case command::commandKeys::eMUL:
			m_commands[i] = new command::Add(tokens[1], tokens[2]);
			break;
		case command::commandKeys::eDIV:
			m_commands[i] = new command::Add(tokens[1], tokens[2]);
			break;
		case command::commandKeys::eDEG:
			m_commands[i] = new command::Add(tokens[1], tokens[2]);
			break;
		case command::commandKeys::ePRINT:
			m_commands[i] = new command::Print(tokens[1]);
			break;
		case command::commandKeys::eJUMP:
			m_commands[i] = new command::Jump(std::stoi(tokens[1]));
			break;
		default:
			break;
		}

		tokens.clear();
	}

	return com;
}

void split(const std::string& line, std::vector<std::string>& res)
{
	std::stringstream ss(line);
	std::string item;

	while (std::getline(ss, item, ' '))
	{
		if (item.length() > 0)
		{
			res.push_back(item);
		}
	}
}

}//namespace cpu