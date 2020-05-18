#include "HolidayDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet* HolidayDataHandler::Execute(Command cmd) const
{
	ResultSet* res = new ResultSet();
	try
	{
		switch (Utility::str2int(cmd.m_szCommandName)) {
		case Utility::str2int("ADD_HOLIDAY"):
			return AddHoliday(cmd);
			break;
		case Utility::str2int("VIEW_HOLIDAY_LIST"):
			return ReadHoliday(cmd);
			break;
		case Utility::str2int("REMOVE_HOLIDAY"):
			return DeleteHoliday(cmd);
			break;
		default:
			cout << "Please Enter Valid Commands" << endl;
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


ResultSet* HolidayDataHandler::AddHoliday(Command cmd) const
{
	if (cmd.m_InputData.size() < 2)
	{
		std::string msg = "Expected 2 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		
		int nLocation_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			nLocation_id = atoi(Lid[0][0].c_str());
		}
		else
		{
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}
		
		query = "INSERT INTO holiday(LOCATION_ID,DATE,DESCRIPTION) VALUES (?,?,?)";
		db.Insert(query, { "I:" + std::to_string(nLocation_id) ,"S:" + Utility::getValueFromMap(cmd.m_InputData, "DATE"),"S:" + Utility::getValueFromMap(cmd.m_InputData, "DESCRIPTION") });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Holiday Record Added Successfully";
		return res;
	}
}


ResultSet* HolidayDataHandler::ReadHoliday(Command cmd) const
{

		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		
		int nLocation_id;
		if (Lid.size() > 0 && Lid[0].size() > 0)
		{
			nLocation_id = atoi(Lid[0][0].c_str());
		}
		else
		{

			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}
		query = "select * from holiday where LOCATION_ID=?";
		res->m_resultData = db.Get(query, { "I:" + std::to_string(nLocation_id) });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_ColumnNames = { "HOL_ID","LOCATION_ID","DATE","DESCRIPTION" };
		res->m_szPrintType = "TABLE";
		return res;
}


ResultSet* HolidayDataHandler::DeleteHoliday(Command cmd) const
{

	if (cmd.m_InputData.size() < 2) 
	{
		std::string msg = "Expected 2 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		
		int nLocation_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) 
		{
			nLocation_id = atoi(Lid[0][0].c_str());
		}
		else
		{
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}

		query = "DELETE FROM holiday WHERE DATE=? AND LOCATION_ID=?";
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "DATE"), "I:" + std::to_string(nLocation_id) });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Holiday Record Removed Successfully";
		return res;
	}
}
