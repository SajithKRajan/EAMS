#include "LocationDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet* LocationDataHandler::execute(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd->command_name))
		{
			case Utility::str2int("ADD_LOCATION"):
				return addLocation(cmd);
				break;
			case Utility::str2int("MODIFY_LOCATION"):
				return updateLocation(cmd);
				break;
			case Utility::str2int("VIEW_LOCATION_LIST"):
				return readLocation();
				break;
			case  Utility::str2int("REMOVE_LOCATION"):
				return deleteLocation(cmd);
				break;
			default:
				std::cout << "Please Enter Valid Commands" << endl;
				break;
		}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return res;
}


ResultSet* LocationDataHandler::addLocation(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();

		std::string query = "INSERT INTO location(LOCATION_NAME) VALUES (?)";
		Database db = Database::Instance();
		db.Insert(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME") });
		cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Location Record Added Successfully";
		return res;
	}
}


ResultSet* LocationDataHandler::readLocation() const
{

		ResultSet* res = new ResultSet();
		std::string query = "select * from location";
		Database db = Database::Instance();
		res->resultData = db.Get(query);
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "LOCATION_ID","LOCATION_NAME" };
		return res;
	
}


ResultSet* LocationDataHandler::updateLocation(Command* cmd) const
{
	if (cmd->inputs.size() != 2) {
		std::string msg = "Expected 2 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		string oldLocationName;
		std::string query = "select LOCATION_NAME from location where LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> LocationResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "OLD_LOCATION_NAME") });
		if (LocationResult.size() > 0) {
			oldLocationName = LocationResult[0][0].c_str();
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such Employee found" << endl;
		}
		if (!(Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME").empty())&& (Utility::getValueFromMap(cmd->inputData, "OLD_LOCATION_NAME")==oldLocationName))
		{
			oldLocationName = Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME");
		}
		query = "UPDATE location SET LOCATION_NAME=? WHERE LOCATION_NAME=?";
		db.Update(query, { "S:" +oldLocationName, "S:" + Utility::getValueFromMap(cmd->inputData, "OLD_LOCATION_NAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Location Record Updated Successfully";
		cout << "updated" << endl;
		return res;
	}
}


ResultSet* LocationDataHandler::deleteLocation(Command* cmd) const
{

	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		// Write code for getting locationid, role id from their names.
		std::string query = "DELETE FROM location WHERE LOCATION_NAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME")});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Record Removed Successfully";
		return res;
	}

}
