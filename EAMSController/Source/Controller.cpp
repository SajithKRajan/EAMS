#include "Controller.h"

void Controller::start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	//char trial;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "LOGIN" << endl;
	Command cmd = inputReader.getCommand("LOGIN");

	ResultSet* res = hanlder->execute(cmd);
	PrintResults pr;
	pr.print(res);
	if (res->isSuccess)
	{
		std::string username = res->resultData[0][0];
		std::string privilages = res->resultData[0][1];
		inputReader.setCommandList(privilages);
		this->emp = new Employee();
		this->emp->setUserName(username);
		cout << endl;
		bool isExit;
		do
		{

			isExit = false;
			Command cmd = inputReader.getNextCommand();

			if (strcmp(cmd.command_name, "EXIT") != 0)
			{
				if (Utility::getValueFromMap(cmd.inputData, "USERNAME").empty()) {
					cmd.inputData.insert({ "USERNAME" , this->emp->getUserName() });
				}
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::enumFromString(cmd.function_handler_name));
				ResultSet* res = hanlder->execute(cmd);
				PrintResults pr;
				pr.print(res);

			}
			else
			{
				isExit = true;
				break;
			}
			cout << endl;
			//cout << "Press Any Key To Continue" << endl;
			system("PAUSE");
			system("CLS");

		} while (!isExit);
	}
	else {
		exit(0);
	}
}