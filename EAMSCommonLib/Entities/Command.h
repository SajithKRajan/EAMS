#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include<map>

using namespace std;
class Command
{
public:
	string function_handler_name;
	char* command_name;
	vector<string> inputs;
	map<string, string> inputdata;
};

