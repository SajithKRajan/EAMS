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
			if (cmd->function_handler_name == "EMPLOYEE") {
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
			}
			else {
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::ROLE);
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
		cin >> trial;
		system("CLS");

	} while (!isExit);
}