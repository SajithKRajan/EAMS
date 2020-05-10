#include "HolidayDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"

ResultSet HolidayDataHandler::execute(Command* cmd) const
{
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


ResultSet HolidayDataHandler::addHoliday(Holiday holiday) const
{
	std::string query = "INSERT INTO holiday(LOCATION_ID,DATE,DESCRIPTION) VALUES (?,?,?)";
	Database db = Database::Instance();
	db.Insert(query, { "S:1","S:2020-12-25","S:Christmas" });

	cout << "Holiday Record Added Successfully" << endl;
	return ResultSet();
}


ResultSet HolidayDataHandler::readHoliday(string locationName) const
{
	std::string query = "select * from holiday where LOCATION_NAME=?";
	Database db = Database::Instance();
	db.Get(query, {"S:TVM" });

	return ResultSet();
}


ResultSet HolidayDataHandler::deleteHoliday(string locationName,string date) const
{
	std::string query = "DELETE FROM holiday WHERE DATE=? AND LOCATION_ID=?";
	Database db = Database::Instance();
	db.Delete(query, { "S:2020-05-01","I:1" });

	cout << "Holiday Record Removed Successfully" << endl;
	return ResultSet();
}
