#include "InputReader.h"


void InputReader::setCommandList(string commandList)
{
	this->commands=Utility::splitString(commandList,',');
}

Command* InputReader::getCommand(string cmdName)

{
	CommandParser* cp = cp->getInstance();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
			cmd->inputData.insert({ header,tempinput });
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
				cmd->inputData.insert({ header,tempinput });
				break;
			}
			case 'y':
			{
				std::cout << "Enter the  " << Utility::toCamelCase(header, '_') << ":";
				cin >> tempinput;
				cmd->inputData.insert({ header,tempinput });
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
	//vector<string> commands{ "ADD_EMPLOYEE","EDIT_EMPLOYEE","MODIFY_EMPLOYEE_DETAILS","VIEW_EMPLOYEE_DETAILS","VIEW_DETAILS","REMOVE_EMPLOYEE_DETAILS","ADD_ABSENCE","ADD_CHECK-IN","ADD_CHECK-OUT","ADD_HOLIDAY","REMOVE_HOLIDAY","ADD_LOCATION","MODIFY_LOCATION","REMOVE_LOCATION","ADD_ROLE","MODIFY_ROLE","REMOVE_ROLE","EXIT" };
	for (int k = 0;k <= (commands.size() - 1);k++)
	{
		cout << k + 1 << " - " << Utility::toCamelCase(commands[k],'_') << endl;
	}
	cin >> ch;
	string commandName = commands.at(ch - 1);
	return getCommand(commandName);
}
