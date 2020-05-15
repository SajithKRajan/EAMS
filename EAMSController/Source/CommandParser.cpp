#include "CommandParser.h"

CommandParser* CommandParser::getInstance() {
	if (!instance) {
		instance = new CommandParser;
		try {
			std::ifstream jsonFile("config.json");
			ptree pt;
			read_json(jsonFile, pt);
			instance->parseCommand(pt);
		}
		catch (exception ex) {
			cout << "Config file read Error" << ex.what();
		}
	}
	return instance;
}

void CommandParser::parseCommand(ptree pt)
{
	try {
		for (auto& commands : pt) {
			Command command;
			auto& function_handler_name = commands.second.get_child("handler_name");
			command.function_handler_name = function_handler_name.data();
			string command_name = commands.second.get_child("command_name").data();
			strncpy_s(command.command_name, command_name.c_str(), sizeof(command.command_name));
			command.command_name[sizeof(command.command_name) - 1] = 0;

			auto& inputs = commands.second.get_child("inputs");
			for (auto& input : inputs) {
				command.inputs.push_back(input.second.get_value< std::string >());
			}
			this->commandList.insert({ commands.first, command });
		}
	}
	catch (exception ex) {
		cout << "Command Parsing failed :" << ex.what();
	}
}

Command CommandParser::getCommand(std::string cmdName)
{
	std::map<std::string, Command>::iterator pos = this->commandList.find(cmdName);
	if (pos == this->commandList.end()) {
		return Command();
	}
	else {
		return pos->second;
	}
}

CommandParser* CommandParser::instance = 0;