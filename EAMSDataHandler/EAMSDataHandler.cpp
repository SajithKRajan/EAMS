#include <iostream>
#include <EAMSFactory.h>

int main()
{
    IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::EMPLOYEE);
    Command* cmd = new Command();
    cmd->command_name = (char*) "ADD_EMPLOYEE";
    hanlder->execute(cmd);
}


