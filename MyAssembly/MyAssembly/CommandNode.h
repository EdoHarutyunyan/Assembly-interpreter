#pragma once
#include <iostream>
#include <vector>
#include <sstream>

struct CommandNode
{
	CommandNode(std::string com, std::string opsize = "DW")
		: m_command{ com }
		, m_opsize{ opsize }
	{
	}

	CommandNode(std::string com, std::vector<std::string> operand, std::string opsize = "DW")
		: CommandNode{com, opsize}
	{
		std::stringstream buff;
		char c;
		m_operand.resize(operand.size());
		for (size_t i = 0; i < operand.size(); ++i)
		{
			buff << operand[i];
			buff >> c;
			buff >> m_operand[i];
			buff.clear();
		}
	}

	CommandNode(std::string com, std::string operand1, int operand2, std::string opsize = "DW")
		: CommandNode{ com, opsize }
	{
		std::stringstream buff;
		char c;
		m_operand.resize(2);

		buff << operand1;
		buff >> c;

		buff >> m_operand[0];
		buff.clear();

		buff << operand2;
		buff >> m_operand[1];
	}

	CommandNode(std::string com, std::string operand1, std::string opsize)
		: CommandNode{ com, opsize }
	{
		std::stringstream buff;
		char c;
		m_operand.resize(2);

		buff << operand1;
		buff >> c;

		buff >> m_operand[0];
	}

	CommandNode(std::string com, size_t label)
		: m_command{com}
	{
		m_operand.resize(1);
		m_operand[0] = label;
	}

	~CommandNode() = default;
	
	std::string m_command;
	std::vector<int> m_operand;
	std::string m_opsize;
};

//class CommandFirstForm : public CommandNode
//{
//public:
//	CommandFirstForm(std::string com, std::vector<std::string> operand, std::string opsize = "DW")
//		: CommandNode(com, opsize)
//	{
//		std::stringstream buff;
//		char c;
//		m_operand.resize(operand.size());
//		for (size_t i = 0; i < operand.size(); ++i)
//		{
//			buff << operand[i];
//			buff >> c;
//			buff >> m_operand[i];
//			buff.clear();
//		}
//	}
//};
//
//class CommandSecondForm : public CommandNode
//{
//public:
//	CommandSecondForm(std::string com, std::vector<std::string> operand, std::string opsize = "DW")
//		: CommandNode(com, opsize)
//	{
//		std::stringstream buff;
//		char c;
//		m_operand.resize(operand.size());
//		
//		buff << operand[0];
//		buff >> c;
//
//		buff >> m_operand[0]; 
//		buff.clear();
//
//		buff << operand[1];
//		buff >> m_operand[1];
//	}
//};