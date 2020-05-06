#include <iostream>
#include "Source/CommandParser.h"
#include <stdlib.h>
#include "Source/InputReader.h"
#include "Common/EAMSFactory.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    //CommandParser* cp = cp->getInstance();
    //Command* cmd = cp->getCommand("VIEW_EMPLOYEE_DETAILS");
    //system("cls");
    //InputReader* in = new InputReader();
    //Command* cmd = in->getCommand("LOGIN");

    IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
    Command* cmd = new Command();
    cmd->command_name = (char*)"ADD_EMPLOYEE";
    hanlder->execute(cmd);

    cout << "fdgfdgfd" <<endl;
}

