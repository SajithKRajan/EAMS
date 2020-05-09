#include "InputReader.h"

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
			std::cout << "Enter " << Utility::toCamelCase(header, '_') << ":";
			cin >> tempinput;
			cmd->inputdata.insert({ header,tempinput });
		}
		else {
			cout << "Do you want to edit " << Utility::toCamelCase(header,'_') << " (y/n)" << endl;
			cin >> temp;
			switch (temp)
			{
			case 'Y':
			{
				std::cout << "Enter the  " << Utility::toCamelCase(header, '_') << ":";
				cin >> tempinput;
				cmd->inputdata.insert({ header,tempinput });
				break;
			}
			case 'y':
			{
				std::cout << "Enter the  " << Utility::toCamelCase(header, '_') << ":";
				cin >> tempinput;
				cmd->inputdata.insert({ header,tempinput });
				break;
			}
			}
		}
		cout << endl;
	}

	return cmd;
}

Command* InputReader::getNextCommand()
{
	int ch;
	cout << "Menu Options" << endl;
	cout << endl;
	vector<string> commands{ "ADD_EMPLOYEE","EDIT_EMPLOYEE","VIEW_EMPLOYEE_DETAILS","MODIFY_EMPLOYEE_DETAILS","REMOVE_EMPLOYEE_DETAILS","ADD_ROLE","VIEW_ROLE_LIST","REMOVE_ROLE","EXIT", };
	for (int k = 0;k <= (commands.size() - 1);k++)
	{
		cout << k + 1 << " - " << Utility::toCamelCase(commands[k],'_') << endl;
	}
	cin >> ch;
	string commandName = commands.at(ch - 1);
	return getCommand(commandName);
}
