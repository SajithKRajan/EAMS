#include "AttendanceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

//Execute methods corresponds to command name
ResultSet* AttendanceDataHandler::Execute(Command cmd) const
{
	ResultSet* res = new ResultSet();
	try
	{
		switch (Utility::str2int(cmd.m_szCommandName)) 
		{
			case Utility::str2int("ADD_CHECK-IN"):
				return AddCheckIn(cmd);
				break;
			case Utility::str2int("ADD_CHECK-OUT"):
				return AddCheckOut(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
				return ReadAttendanceSummaryOfWeek(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
				return ReadAttendanceSummaryOfWeek(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
				return ReadAttendanceSummaryOfMonth(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
				return ReadAttendanceSummaryOfMonth(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION"):
				return ReadLocationAttendance(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_WORK_HOURS"):
				return ReadWorkHours(cmd);
				break;
			case  Utility::str2int("VIEW_WORK_HOURS"):
				return ReadWorkHours(cmd);
				break;
			case Utility::str2int("VIEW_TOTAL_WORK_HOURS_OF_A_LOCATION"):
				return ReadLocationWorkHours(cmd);
				break;
			case Utility::str2int("VIEW_ORGANIZATION_WORK_HOURS"):
				return ReadOrganizationWorkHours();
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


ResultSet* AttendanceDataHandler::AddCheckIn(Command cmd) const
{
	ResultSet* res = new ResultSet();

	int nEmployeeId;
	int nLocationId;

	std::string query = "select employee.EMP_ID,LOCATION_ID from employee where employee.USERNAME=?";
	Database db = Database::Instance();
	std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME")});
	
	if (Empid.size() > 0 && Empid[0].size() > 0) 
	{
		nEmployeeId = atoi(Empid[0][0].c_str());
		nLocationId = atoi(Empid[0][1].c_str());
	}
	else 
	{
		std::string msg = "No such employee found";
		throw EAMSException(msg.c_str());
	}

	query = "select * from attendance where EMP_ID=? AND DATE(CHECK_IN)=CURDATE()";
	std::vector<std::vector<std::string>> test = db.Get(query, { "I:" + std::to_string(nEmployeeId) });

	if (test.size() == 0)
	{
		query = "INSERT INTO attendance(EMP_ID,LOCATION_ID,CHECK_IN) VALUES (?,?,now())";
		db.Insert(query, { "I:" + std::to_string(nEmployeeId),"I:" + std::to_string(nLocationId) });

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Employee Record Added Successfully";

		return res;
	}
	else
	{
		std::string msg = "Already added record";
		throw EAMSException(msg.c_str());
	}

}


ResultSet* AttendanceDataHandler::AddCheckOut(Command cmd) const
{
	ResultSet* res = new ResultSet();

	std::string strQuery = "select employee.EMP_ID from employee where employee.USERNAME=?";
	Database db = Database::Instance();
	std::vector<std::vector<std::string>> Empid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });

	int nEmployeeId;
	if (Empid.size() > 0 && Empid[0].size() > 0) 
	{
		nEmployeeId = atoi(Empid[0][0].c_str());
	}
	else 
	{
		std::string msg = "No such employee found";
		throw EAMSException(msg.c_str());
	}

	strQuery = "UPDATE attendance SET CHECK_OUT=now(),TOTAL_HRS=TIMESTAMPDIFF(HOUR,attendance.CHECK_IN,attendance.CHECK_OUT) WHERE EMP_ID=? AND DATE(CHECK_IN)=CURDATE()";
	db.Update(strQuery, { "I:" + std::to_string(nEmployeeId) });

	res->m_IsSuccess = true;
	res->m_IsToBePrint = true;
	res->m_szPrintType = "MESSAGE";
	res->m_szMessage = "Employee Record Added Successfully";

	return res;
}


ResultSet* AttendanceDataHandler::ReadAttendanceSummaryOfWeek(Command cmd) const
{
	if (cmd.m_InputData.size() != 1) 
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();

		std::string strQuery = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "USERNAME") });

		int nEmployeeId;
		if (Empid.size() > 0 && Empid[0].size() > 0) 
		{
			nEmployeeId = atoi(Empid[0][0].c_str());
		}
		else 
		{
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		strQuery = "select DATE(CHECK_IN), TIME(CHECK_IN) , TIME(CHECK_OUT)  from attendance where EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE()";
		res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nEmployeeId) });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "DATE","CHECK_IN","CHECK_OUT" };

		return res;
	}
}


ResultSet* AttendanceDataHandler::ReadAttendanceSummaryOfMonth(Command cmd) const
{
	if (cmd.m_InputData.size() != 1)
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();

		std::string strQuery = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "USERNAME") });
		
		int nEmployeeId;
		if (Empid.size() > 0 && Empid[0].size() > 0)
		{
			nEmployeeId = atoi(Empid[0][0].c_str());
		}
		else
		{
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		strQuery = "select DATE(CHECK_IN) AS DATE, TIME(CHECK_IN) AS CHECK_IN, TIME(CHECK_OUT) AS CHECK_OUT from attendance where EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 30 DAY) AND CURDATE()";
		res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nEmployeeId) });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "DATE","CHECK_IN","CHECK_OUT" };

		return res;
	}
}


ResultSet* AttendanceDataHandler::ReadLocationAttendance(Command cmd) const
{

	ResultSet* res = new ResultSet();

	std::string strQuery = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
	Database db = Database::Instance();
	std::vector<std::vector<std::string>> Lid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
	
	int nLocationId;
	if (Lid.size() > 0 && Lid[0].size() > 0) 
	{
		nLocationId = atoi(Lid[0][0].c_str());
	}
	else 
	{

		std::string msg = "No such location found";
		throw EAMSException(msg.c_str());
	}

	strQuery = "select DATE(CHECK_IN) AS DATE, COUNT(*) AS COUNT FROM attendance WHERE LOCATION_ID = ? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
	res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nLocationId) });
	
	res->m_IsSuccess = true;
	res->m_IsToBePrint = true;
	res->m_szPrintType = "TABLE";
	res->m_ColumnNames = { "DATE","COUNT" };

	return res;
}


ResultSet* AttendanceDataHandler::ReadWorkHours(Command cmd) const
{
	if (cmd.m_InputData.size() < 1)
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();
		std::string strQuery = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "USERNAME") });
		
		int nEmployeeId;
		if (Empid.size() > 0 && Empid[0].size() > 0) 
		{
			nEmployeeId = atoi(Empid[0][0].c_str());
		}
		else 
		{

			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		strQuery = "select DATE(CHECK_IN), TOTAL_HRS FROM attendance WHERE EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 30 DAY) AND CURDATE()";
		res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nEmployeeId) });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "DATE","TOTAL_HRS" };
		return res;
	}
}


ResultSet* AttendanceDataHandler::ReadLocationWorkHours(Command cmd) const
{
	if (cmd.m_InputData.size() < 1) 
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string strQuery = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(strQuery, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		
		int nLocationId;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			nLocationId = atoi(Lid[0][0].c_str());
		}
		else 
		{
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}
		
		strQuery = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS  FROM attendance WHERE LOCATION_ID=? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
		res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nLocationId) });

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "DATE","TOTAL_HRS" };

		return res;
	}
}
ResultSet* AttendanceDataHandler::ReadOrganizationWorkHours() const
{

	ResultSet* res = new ResultSet();
	std::string strQuery = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS FROM attendance WHERE  DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
	Database db = Database::Instance();
	res->m_resultData = db.Get(strQuery);

	res->m_IsSuccess = true;
	res->m_IsToBePrint = true;
	res->m_szPrintType = "TABLE";
	res->m_ColumnNames = { "DATE","TOTAL_HRS" };

	return res;
}
