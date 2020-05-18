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
//Member functions
public:
	void SetCommandList(string commandList);
	Command GetCommand(string cmdName);
	Command GetNextCommand();

//Member variable
private:
	vector<string> m_Commands;

};

