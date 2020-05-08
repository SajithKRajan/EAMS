#include "Controller.h"

void Controller::start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	char trial;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "	LOGIN STARTS	" << endl;
	Command* cmd = inputReader.getCommand("LOGIN");
	hanlder->execute(cmd);
	cout << endl;
	bool isExit;
	do
	{
	
		isExit = false;
		Command* cmd=inputReader.getNextCommand();
		if (cmd->command_name != "EXIT")
		{
			hanlder->execute(cmd);
			
		}
		else
		{
			isExit = true;
			break;
		}
		cin >> trial;
		system("CLS");

	} while (!isExit);
}