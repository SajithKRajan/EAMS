#pragma once
//To read command from json file and parse commands

#include "Entities/Command.h"
#include <map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using boost::property_tree::ptree;
class CommandParser
{
//Member functions
public:
    static CommandParser* GetInstance();
    void ParseCommand(ptree pt);
    Command GetCommand(std::string cmdName);

//Member variables
private:
    static CommandParser* m_Instance;
    map<std::string, Command> m_CommandList;
    CommandParser() {
    }

};


