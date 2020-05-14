#pragma once
#include <iostream>
#include <string.h>
#include "Entities/Command.h"
#include "CommandParser.h"
#include "Utilities/Utility.h"
#include <vector>


using namespace std;

class InputReader
{
private:
	vector<string> commands;
public:
	void setCommandList(string commandList);
	Command getCommand(string cmdName);
	Command getNextCommand();
};

