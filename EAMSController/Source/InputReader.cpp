#include "InputReader.h"

//getting commands from privilege
void InputReader::SetCommandList(string commandList)
{
	this->m_Commands=Utility::splitString(commandList,',');
}

//getting input data from user corresponds to command
Command InputReader::GetCommand(string cmdName)
{
	CommandParser* cp = CommandParser::GetInstance();
	Command cmd = cp->GetCommand(cmdName);
	string tempinput;
	char temp;

	for (string strInput : cmd.m_Inputs)
	{
		string header = strInput.substr(strInput.find(':') + 1, strInput.length());
		bool mandatory = false;
		if (-1 != header.find('*'))
		{
			header = header.substr(0, header.length() - 1);
			mandatory = true;
		}
		if (mandatory)
		{
			std::cout << "Enter " << Utility::toCamelCase(header, '_') << ":";
			cin >> tempinput;
			cmd.m_InputData.insert({ header,tempinput });
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
				cmd.m_InputData.insert({ header,tempinput });
				break;
			}
			case 'y':
			{
				std::cout << "Enter the  " << Utility::toCamelCase(header, '_') << ":";
				cin >> tempinput;
				cmd.m_InputData.insert({ header,tempinput });
				break;
			}
			}
		}
		cout << endl;
	}
	return cmd;
}

//getting next command
Command InputReader::GetNextCommand()
{
	int ch;
	cout << "Menu Options" << endl;
	cout << endl;
	
	for (int k = 0;k <= (m_Commands.size() - 1);k++)
	{
		cout << k + 1 << " - " << Utility::toCamelCase(m_Commands[k],'_') << endl;
	}
	cin >> ch;
	string strCommandName = m_Commands.at(ch - 1);
	return GetCommand(strCommandName);
}
