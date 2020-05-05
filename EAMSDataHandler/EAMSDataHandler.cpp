#include <iostream>
#include <EAMSFactory.h>


int main()
{
    IDataHandler* hanlder = EAMSFactory::Instance().getIDataHandler(HandlerTypes::ATTENDANCE);
    Command* cmd = new Command();
    cmd->command_name = (char*) "VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION";
    hanlder->execute(cmd);
}


