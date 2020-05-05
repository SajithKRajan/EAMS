#include <iostream>
#include <EAMSFactory.h>


int main()
{
    IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::ROLE);
    Command* cmd = new Command();
    cmd->command_name = (char*) "MODIFY_ROLE";
    hanlder->execute(cmd);
}


