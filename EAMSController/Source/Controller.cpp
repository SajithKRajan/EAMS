#include "Controller.h"

void Controller::Start()
{
	IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
	InputReader inputReader;
	cout << "*-*-*-*-*-*-*-*-*-*-*- WELCOME TO QAMS *-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << endl;
	cout << "LOGIN" << endl;
	Command cmd = inputReader.GetCommand("LOGIN");

	ResultSet* res = hanlder->Execute(cmd);

	PrintResults printResult;
	printResult.Print(res);

	if (res->m_IsSuccess)
	{
		std::string strUsername = res->m_resultData[0][0];
		std::string strPrivilages = res->m_resultData[0][1];
		inputReader.SetCommandList(strPrivilages);
		this->emp = new Employee();
		this->emp->SetUserName(strUsername);
		cout << endl;
		bool isExit;
		
		do
		{
			isExit = false;
			Command cmd = inputReader.GetNextCommand();

			if (strcmp(cmd.m_szCommandName, "EXIT") != 0)
			{
				if (Utility::getValueFromMap(cmd.m_InputData, "USERNAME").empty()) {
					cmd.m_InputData.insert({ "USERNAME" , this->emp->GetUserName() });
				}

				hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EnumFromString(cmd.m_strFunctionHandlerName));

				ResultSet* res = hanlder->Execute(cmd);
				printResult.Print(res);
			}
			else
			{
				isExit = true;
				break;
			}

			cout << endl;
			system("PAUSE");
			system("CLS");

		} 
		while (!isExit);
	}
	else 
	{
		exit(0);
	}
}