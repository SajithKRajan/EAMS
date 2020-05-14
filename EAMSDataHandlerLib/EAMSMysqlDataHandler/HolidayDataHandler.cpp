#include "HolidayDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet* HolidayDataHandler::execute(Command cmd) const
{
	ResultSet* res = new ResultSet();
	try
	{
		switch (Utility::str2int(cmd.command_name)) {
		case Utility::str2int("ADD_HOLIDAY"):
			return addHoliday(cmd);
			break;
		case Utility::str2int("VIEW_HOLIDAY_LIST"):
			return readHoliday(cmd);
			break;
		case Utility::str2int("REMOVE_HOLIDAY"):
			return deleteHoliday(cmd);
			break;
		default:
			cout << "Please Enter Valid Commands" << endl;
			break;
		}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return res;
}


ResultSet* HolidayDataHandler::addHoliday(Command cmd) const
{
	cout << "HolidayDataHandler::addHoliday";
	if (cmd.inputs.size() < 2) {
		std::string msg = "Expected 2 arguments but got" + cmd.inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		// Write code for getting EMP_ID FROM USERNAME.
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such location found" << endl;
		}
		query = "INSERT INTO holiday(LOCATION_ID,DATE,DESCRIPTION) VALUES (?,?,?)";

		db.Insert(query, { "I:" + std::to_string(location_id) ,"S:" + Utility::getValueFromMap(cmd.inputData, "DATE"),"S:" + Utility::getValueFromMap(cmd.inputData, "DESCRIPTION") });
		cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Holiday Record Added Successfully";
		return res;
	}
}


ResultSet* HolidayDataHandler::readHoliday(Command cmd) const
{
	if (cmd.inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd.inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {

			cout << "ERR:No such location found" << endl;
		}
		query = "select * from holiday where LOCATION_ID=?";
		res->resultData = db.Get(query, { "I:" + std::to_string(location_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->ColumnNames = { "HOL_ID","LOCATION_ID","DATE","DESCRIPTION" };
		res->printType = "TABLE";
		return res;
	}
}


ResultSet* HolidayDataHandler::deleteHoliday(Command cmd) const
{

	if (cmd.inputData.size() != 2) {
		std::string msg = "Expected 2 arguments but got" + cmd.inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where LOCATION.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			
			cout << "ERR:No such location found" << endl;
		}

		query = "DELETE FROM holiday WHERE DATE=? AND LOCATION_ID=?";
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "DATE"), "I:" + std::to_string(location_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Holiday Record Removed Successfully";
		return res;
	}
}
