#include "Controller.h"

void Controller::start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	char trial;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "LOGIN" << endl;
	Command* cmd = inputReader.getCommand("LOGIN");
	hanlder->execute(cmd);
	cout << endl;
	bool isExit;
	do
	{
	
		isExit = false;
		Command* cmd=inputReader.getNextCommand();
		if ( strcmp(cmd->command_name, "EXIT")!=0)
		{
			if (cmd->function_handler_name == "HOLIDAY") {
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::HOLIDAY);
			}
			else {
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::ABSENCE);
			}
			ResultSet res = hanlder->execute(cmd);
			PrintResults pr;
			pr.print(res);
			
		}
		else
		{
			isExit = true;
			break;
		}
		cout << endl;
		cout << "Press Any Key And Enter For Menu Options " << endl;
		cin >> trial;
		system("CLS");

	} while (!isExit);
}