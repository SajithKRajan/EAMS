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
            cout << "Read Error" << ex.what();
        }
    }
    return instance;
}

void CommandParser::parseCommand(ptree pt)
{
    try {
        for (auto& commands : pt) {
            Command* command = new Command();
            auto& function_handler_name = commands.second.get_child("handler_name");
            command->function_handler_name = function_handler_name.data();
            string command_name = commands.second.get_child("command_name").data();
            int length = command_name.length();
            char* cstr= new char[length];
            command_name.copy(cstr, length);
            cstr[length] = '\0';
            command->command_name = cstr;
            auto& inputs = commands.second.get_child("inputs");
            for (auto& input : inputs) {
                command->inputs.push_back(input.second.get_value< std::string >());
            }
            this->commandList.insert({ commands.first, command });
        }
    }
    catch (exception ex) {
        cout << "Parse Error" << ex.what();
    }
}

Command* CommandParser::getCommand(std::string cmdName)
{
    std::map<std::string, Command*>::iterator pos = this->commandList.find(cmdName);
    if (pos == this->commandList.end()) {
        return NULL;
    }
    else {
        return pos->second;
    }
}

CommandParser* CommandParser::instance = 0;