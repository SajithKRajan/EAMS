#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include<map>

class Command
{
//Member variables
public:
	std::string m_strFunctionHandlerName;
	char m_szCommandName[50];
	std::vector<std::string> m_Inputs;
	std::map<std::string, std::string> m_InputData;
};

