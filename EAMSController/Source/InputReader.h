#pragma once
#pragma once
#include <iostream>
#include <string.h>
#include "Entities/Command.h"
#include "CommandParser.h"

using namespace std;

class InputReader
{
public:
	Command* getCommand(string cmdName);
	Command* getNextCommand();
};