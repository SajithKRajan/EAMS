#include "Controller.h"

void Controller::start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	cout << "*****LOGIN START*******" << endl;
	Command* cmd = inputReader.getCommand("LOGIN");
	hanlder->execute(cmd);
	cout << endl;
	cout << "Login successful" << endl;
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
		//system("cls");

	} while (!isExit);
}