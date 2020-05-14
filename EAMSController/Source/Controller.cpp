#include "Controller.h"

void Controller::start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	char trial;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "LOGIN" << endl;
	Command cmd = inputReader.getCommand("LOGIN");
	//Command* command = new Command();
	//std::copy(std::begin(cmd.command_name), std::end(cmd.command_name), std::begin(command->command_name));
	////command->command_name = cmd.command_name;
	//command->function_handler_name = cmd.function_handler_name;
	//command->inputData = cmd.inputData;
	//command->inputs=cmd.inputs;
	ResultSet* res = hanlder->execute(cmd);
	// todo handle error case
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
		//Command* command = new Command();
		//std::copy(std::begin(cmd.command_name), std::end(cmd.command_name), std::begin(command->command_name));
		//command->function_handler_name = cmd.function_handler_name;
		//command->inputData = cmd.inputData;
		//command->inputs = cmd.inputs;
		if (strcmp(cmd.command_name, "EXIT") != 0)
		{
			if (Utility::getValueFromMap(cmd.inputData,"USERNAME").empty()) {
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
		cout << "Press Any Key And Enter For Menu Options " << endl;
		cin >> trial;
		system("CLS");

	} while (!isExit);
}