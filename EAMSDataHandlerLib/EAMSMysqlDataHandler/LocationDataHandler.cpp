#include "LocationDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

//Execute methods corresponds to command name
ResultSet* LocationDataHandler::Execute(Command cmd) const
{
	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd.m_szCommandName))
		{
			case Utility::str2int("ADD_LOCATION"):
				return AddLocation(cmd);
				break;
			case Utility::str2int("MODIFY_LOCATION"):
				return UpdateLocation(cmd);
				break;
			case Utility::str2int("VIEW_LOCATION_LIST"):
				return ReadLocation();
				break;
			case  Utility::str2int("REMOVE_LOCATION"):
				return DeleteLocation(cmd);
				break;
			default:
				break;
		}
	}
	catch (EAMSException ex) 
	{
		res->m_IsSuccess = false;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = ex.what();
	}
	return res;
}


ResultSet* LocationDataHandler::AddLocation(Command cmd) const
{
	if (cmd.m_InputData.size() < 1) 
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "select * from location where LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> TestResult = db.Get(query,{ "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		
		if (TestResult.size() == 0)
		{
			std::string query = "INSERT INTO location(LOCATION_NAME) VALUES (?)";
			db.Insert(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
			
			res->m_IsSuccess = true;
			res->m_IsToBePrint = true;
			res->m_szPrintType = "MESSAGE";
			res->m_szMessage = "Location Record Added Successfully";
			return res;
		}
		else 
		{
			std::string msg = "Record Already exist";
			throw EAMSException(msg.c_str());
		}
	}
}


ResultSet* LocationDataHandler::ReadLocation() const
{

		ResultSet* res = new ResultSet();
		std::string query = "select * from location";
		Database db = Database::Instance();
		res->m_resultData = db.Get(query);

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "LOCATION_ID","LOCATION_NAME" };
		return res;
	
}


ResultSet* LocationDataHandler::UpdateLocation(Command cmd) const
{
	if (cmd.m_InputData.size() < 2) 
	{
		std::string msg = "Expected 2 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();
		string oldLocationName;
		std::string query = "select LOCATION_NAME from location where LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> LocationResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "OLD_LOCATION_NAME") });
		
		if (LocationResult.size() > 0)
		{
			oldLocationName = LocationResult[0][0].c_str();
		}
		else
		{
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}

		if (!(Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME").empty())&& (Utility::getValueFromMap(cmd.m_InputData, "OLD_LOCATION_NAME")==oldLocationName))
		{
			oldLocationName = Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME");
		}

		query = "UPDATE location SET LOCATION_NAME=? WHERE LOCATION_NAME=?";
		db.Update(query, { "S:" +oldLocationName, "S:" + Utility::getValueFromMap(cmd.m_InputData, "OLD_LOCATION_NAME") });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Location Record Updated Successfully";
		return res;
	}
}


ResultSet* LocationDataHandler::DeleteLocation(Command cmd) const
{

	if (cmd.m_InputData.size() < 1)
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "DELETE FROM location WHERE LOCATION_NAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME")});
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Record Removed Successfully";
		return res;
	}
}
