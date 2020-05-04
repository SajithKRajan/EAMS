#pragma once
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
class Command
{
public:
	string function_handler_name;
	char* command_name;
	vector<string> inputs;
};

