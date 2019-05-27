#pragma once

#include <unordered_map>
#include <map>
#include <string>
#include <sstream>

namespace type
{

std::map<std::string, size_t> type_map = {
	{"CHAR", 0},
	{"BYTE", 1},
	{"WORD", 2},
	{"DWORD", 3},
	{"QWORD", 4}		   
};

std::unordered_map<std::string, size_t> type_table;

enum Type 
{
	CHAR = 0,
	BYTE = 1,
	WORD = 2,
	DWORD = 3,
	QWORD = 4
};

void UpdateTypeTable(const std::string& identifier, const size_t offset/*const Type type*/)
{
	std::stringstream ss;
	char firstSimbol;
	size_t secondSimbol;

	ss << identifier;
	ss >> firstSimbol;

	//Check identifier
	if (firstSimbol == 'A')
	{
		ss >> secondSimbol;

		if (ss.eof())
		{
			if (secondSimbol >= 0 && secondSimbol <= 7)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	ss.clear();

	if (firstSimbol == 'R')
	{
		ss >> secondSimbol;
		if (ss.eof())
		{
			if (secondSimbol >= 0 && secondSimbol <= 7)
			{
				throw std::invalid_argument("Invalid identifier : " + identifier);
			}
		}
	}

	type_table[identifier]  = offset;
}

Type to_enum(const size_t t)
{
	return static_cast<Type>(t);
}

char to_char(const std::string& from)
{
	std::stringstream buff;
	char to;

	buff << from;
	buff >> to;

	return to;
}

}//namespace type
