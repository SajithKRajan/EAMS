#include "AbsenceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

//Execute methods corresponds to commands
ResultSet* AbsenceDataHandler::Execute(Command cmd) const
{
	ResultSet* res = new ResultSet();

	try 
	{
		switch (Utility::str2int(cmd.m_szCommandName)) 
		{
			case Utility::str2int("ADD_ABSENCE"):
				return AddAbsence(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_ABSENCE_LIST"):
				return ReadAbsence(cmd);
				break;
			case Utility::str2int("VIEW_ABSENCE_LIST"):
				return ReadAbsence(cmd);
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

ResultSet* AbsenceDataHandler::AddAbsence(Command cmd) const
{

		ResultSet* res = new ResultSet();

		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });
		
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

		query = "INSERT INTO absence(EMP_ID,DATE) VALUES (?,now())";
		db.Insert(query,{ "I:"+std::to_string(nEmployeeId) });

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Absence Record Added Successfully";

		return res;

}


ResultSet* AbsenceDataHandler::ReadAbsence(Command cmd) const
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
		
		int nEmployee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0)
		{
			nEmployee_id = atoi(Empid[0][0].c_str());
		}
		else 
		{
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		strQuery = "select *  from absence where EMP_ID=?";
		res->m_resultData = db.Get(strQuery, { "I:" + std::to_string(nEmployee_id) });

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_ColumnNames = { "ABS_ID","EMP_ID","DATE" };
		res->m_szPrintType = "TABLE";

		return res;
	}

}


