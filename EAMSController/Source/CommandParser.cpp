#include "CommandParser.h"

CommandParser* CommandParser::GetInstance() {
	if (!m_Instance) {
		m_Instance = new CommandParser;
		try {
			std::ifstream jsonFile("config.json");
			ptree pt;
			read_json(jsonFile, pt);
			m_Instance->ParseCommand(pt);
		}
		catch (exception ex) {
			cout << "Config file read Error" << ex.what();
		}
	}
	return m_Instance;
}

void CommandParser::ParseCommand(ptree pt)
{
	try {
		for (auto& commands : pt) {
			Command command;
			auto& function_handler_name = commands.second.get_child("handler_name");
			command.m_strFunctionHandlerName = function_handler_name.data();
			string command_name = commands.second.get_child("command_name").data();
			strncpy_s(command.m_szCommandName, command_name.c_str(), sizeof(command.m_szCommandName));
			command.m_szCommandName[sizeof(command.m_szCommandName) - 1] = 0;

			auto& inputs = commands.second.get_child("inputs");
			for (auto& input : inputs) {
				command.m_Inputs.push_back(input.second.get_value< std::string >());
			}
			this->m_CommandList.insert({ commands.first, command });
		}
	}
	catch (exception ex) {
		cout << "Command Parsing failed :" << ex.what();
	}
}

Command CommandParser::GetCommand(std::string cmdName)
{
	std::map<std::string, Command>::iterator pos = this->m_CommandList.find(cmdName);
	if (pos == this->m_CommandList.end()) {
		return Command();
	}
	else
	{
		return pos->second;
	}
}

CommandParser* CommandParser::m_Instance = 0;