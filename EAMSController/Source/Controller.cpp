#include "Controller.h"

void Controller::Start()
{
	//This represents a handler to execute the authentication function from employee class
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "LOGIN" << endl;
	//Getting input data corresponds to command login
	Command cmd = inputReader.GetCommand("LOGIN");
	//Execute datahandler using the command data
	ResultSet* res = hanlder->Execute(cmd);

	PrintResults printResult;
	//Calling print method that displays the result data
	printResult.Print(res);

	//checking whether authentication completed successfully
	if (res->m_IsSuccess)
	{
		//getting username of current user
		std::string strUsername = res->m_resultData[0][0];
		//getting privileges corresponds to current user role
		std::string strPrivilages = res->m_resultData[0][1];
		//displays the privileges corresponds to current users role
		inputReader.SetCommandList(strPrivilages);
		this->emp = new Employee();
		//set username of current username
		this->emp->SetUserName(strUsername);
		cout << endl;
		bool isExit;
		
		do
		{
			isExit = false;
			//getting next command
			Command cmd = inputReader.GetNextCommand();
			//checking whether command is not "EXIT"
			if (strcmp(cmd.m_szCommandName, "EXIT") != 0)
			{
				//checking whether username from command input is empty
				if (Utility::getValueFromMap(cmd.m_InputData, "USERNAME").empty()) {
					//if empty assign current user's username as default
					cmd.m_InputData.insert({ "USERNAME" , this->emp->GetUserName() });
				}

				//getting datahandler corresponds to function handler name from command
				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EnumFromString(cmd.m_strFunctionHandlerName));
				//execute the datahandler using command input data
				ResultSet* res = hanlder->Execute(cmd);
				//dispaly result
				printResult.Print(res);
			}
			else
			{
				isExit = true;
				break;
			}

			cout << endl;
			//pause screen until press any key
			system("PAUSE");
			//clear screen
			system("CLS");

		} 
		while (!isExit);
	}
	else 
	{
		exit(0);
	}
}