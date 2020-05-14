#pragma once
#include "Entities/Command.h"
#include <map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using boost::property_tree::ptree;
class CommandParser
{
private:
    static CommandParser* instance;
    map<std::string, Command> commandList;
    CommandParser() {
    }
public:
    static CommandParser* getInstance();
    void parseCommand(ptree pt);
    Command getCommand(std::string cmdName);
};


