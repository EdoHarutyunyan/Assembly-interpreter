#pragma once

class CPU;

class BaseCommand
{
public:
	virtual void Execute(CPU& cpu) const = 0;

	virtual ~BaseCommand() = default;
};