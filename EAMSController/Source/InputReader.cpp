#include "InputReader.h"
#include "Entities/Command.h"
#include "Source/CommandParser.h"

Command* InputReader::getCommand(string cmdName)

{
	CommandParser* cp = cp->getInstance();
	Command* cmd = cp->getCommand(cmdName);
	string tempinput;
	char temp;

	for (string input : cmd->inputs)
	{
		string header = input.substr(input.find(':') + 1, input.length());
		bool mandatory = false;
		if (-1 != header.find('*'))
		{
			header = header.substr(0, header.length() - 1);
			mandatory = true;
		}
		if (mandatory) {
			std::cout << "enter the  " << header << endl;
			cin >> tempinput;
			cmd->inputdata.insert({ header,tempinput });
		}
		else {
			cout << "Do you want to edit " << header << " (y/n)" << endl;
			cin >> temp;
			switch (temp)
			{
			case 'Y':
			{
				std::cout << "enter the  " << header << endl;
				cin >> tempinput;
				cmd->inputdata.insert({ header,tempinput });
				break;
			}
			case 'y':
			{
				std::cout << "enter the  " << header << endl;
				cin >> tempinput;
				cmd->inputdata.insert({ header,tempinput });
				break;
			}

			}



		}
	}

	return cmd;
}

Command* InputReader::getNextCommand()
{
	int ch;
	vector<string> commands{ "ADD_EMPLOYEE","VIEW_EMPLOYEE_DETAILS","VIEW_EMPLOYEE_WORK_HOURS", "ADD_LOCATION" };
	for (int k = 0;k <= (commands.size() - 1);k++)
	{
		cout << k + 1 << " " << commands[k] << endl;
	}
	cout << "enter the choice" << endl;
	cin >> ch;

	string commandName = commands.at(ch - 1);
	Command* getCommand(string commandName);
}