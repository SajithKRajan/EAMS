#include "HolidayDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet HolidayDataHandler::execute(Command* cmd) const
{
	std::cout << "HolidayDataHandler - > execute"<<endl;
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_HOLIDAY"):
		addHoliday(Holiday());
		break;
	case Utility::str2int("VIEW_HOLIDAY_LIST"):
		readHoliday("");
		break;
	case Utility::str2int("REMOVE_HOLIDAY"):
		deleteHoliday("","");
		break;
	default:
		cout << "Please Enter Valid Commands" << endl;
		break;
	}
	return ResultSet();
}


void HolidayDataHandler::addHoliday(Holiday holiday) const
{
	std::cout << "addHoliday - > execute";
}


Holiday HolidayDataHandler::readHoliday(string locationName) const
{
	std::cout << "readHoliday - > execute";
	return Holiday();
}


void HolidayDataHandler::deleteHoliday(string locationName,string date) const
{
	std::cout << "deleteHoliday - > execute";
}
