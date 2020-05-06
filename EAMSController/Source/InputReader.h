#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class InputReader
{
private:

public:
	Command* getCommand(string cmdName);
	Command* getNextCommand();
};

