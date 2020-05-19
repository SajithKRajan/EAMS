#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include <EAMSMysqlDataHandler/EAMSException.h>

//Execute methods corresponds to command name
ResultSet* EmployeeDataHandler::Execute(Command cmd) const
{
	ResultSet* res = new ResultSet();
	try 
	{
		switch (Utility::str2int(cmd.m_szCommandName)) 
		{
			case Utility::str2int("LOGIN"):
				return Authenticate(cmd);
				break;
			case Utility::str2int("ADD_EMPLOYEE"):
				return AddEmployee(cmd);
				break;
			case Utility::str2int("EDIT_EMPLOYEE"):
				return UpdateEmployee(cmd);
				break;
			case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
				return ReadEmployee(cmd);
				break;
			case Utility::str2int("VIEW_DETAILS"):
				return ReadEmployee(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_LIST"):
				return ReadEmployeeList();
				break;
			case Utility::str2int("MODIFY_EMPLOYEE_DETAILS"):
				return ModifyEmployeeDetails(cmd);
				break;
			case Utility::str2int("REMOVE_EMPLOYEE_DETAILS"):
				return DeleteEmployee(cmd);
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


ResultSet* EmployeeDataHandler::AddEmployee(Command cmd) const
{


	if (cmd.m_InputData.size() != 4) 
	{
		std::string msg = "Expected 4 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
		int nLocationId;
		if (Lid.size()>0 && Lid[0].size() > 0) 
		{
			nLocationId = atoi(Lid[0][0].c_str());
		}
		else {
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}

		query = "select role.ROLE_ID from role where role.NAME=?";
		std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });
		
		int nRole_id;
		if (Rid.size() > 0 && Rid[0].size() > 0) 
		{
			nRole_id = atoi(Rid[0][0].c_str());
		}
		else
		{
			std::string msg = "No such role found";
			throw EAMSException(msg.c_str());
		}


		query = "INSERT INTO employee(USERNAME,PASSWORD,ROLE_ID,LOCATION_ID) VALUES (?,?,?,?)";
		db.Insert(query,{ "S:"+ Utility::getValueFromMap(cmd.m_InputData,"USERNAME"),"S:"+ Utility::getValueFromMap(cmd.m_InputData, "PASSWORD"),"I:" + std::to_string(nRole_id),"I:" + std::to_string(nLocationId)});
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Employee Record Added Successfully";

		return res;
	}
}


ResultSet* EmployeeDataHandler::ReadEmployee(Command cmd) const
{
	if (cmd.m_InputData.size() != 1) 
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();
		std::string query = "select EMP_ID,USERNAME,FIRSTNAME,LASTNAME,ROLE_ID,LOCATION_ID from employee where USERNAME=?";
		Database db = Database::Instance();
		res->m_resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });
		
		if (res->m_resultData.size() > 0)
		{
			res->m_IsSuccess = true;
			res->m_IsToBePrint = true;
			res->m_ColumnNames = { "EMPLOYEE ID","USERNAME","FIRSTNAME","LASTNAME","ROLE_ID","LOCATION_ID" };
			res->m_szPrintType = "TABLE";
			return res;
		}
		else
		{
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
	}
}


ResultSet* EmployeeDataHandler::ReadEmployeeList() const
{
		try
		{
			ResultSet* res = new ResultSet();
			std::string query = "select EMP_ID,USERNAME,FIRSTNAME,LASTNAME,ROLE_ID,LOCATION_ID from employee";
			Database db = Database::Instance();
			res->m_resultData = db.Get(query);

			res->m_IsSuccess = true;
			res->m_IsToBePrint = true;
			res->m_ColumnNames = { "EMPLOYEE ID","USERNAME","FIRSTNAME","LASTNAME","ROLE_ID","LOCATION_ID" };
			res->m_szPrintType = "TABLE";
			return res;
		}
		catch (exception e)
		{
			cout << "ERR:"<<e.what();
		}
}


ResultSet* EmployeeDataHandler::UpdateEmployee(Command cmd) const
{

	try
	{
		std::string strFirstName;
		std::string strLastname;
		std::string strPassword;

		ResultSet* res = new ResultSet();
		std::string query = "select FIRSTNAME,LASTNAME,PASSWORD from employee where USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> employeeResult = db.Get(query, {"S:" +Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });
		
		if (employeeResult.size() > 0)
		{
			strFirstName = employeeResult[0][0].c_str();
			strLastname = employeeResult[0][1].c_str();
			strPassword = employeeResult[0][2].c_str();
			
		}
		else
		{
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}

		if (!(Utility::getValueFromMap(cmd.m_InputData, "FIRSTNAME").empty()))
		{
			strFirstName = Utility::getValueFromMap(cmd.m_InputData, "FIRSTNAME");
		}
		if (!(Utility::getValueFromMap(cmd.m_InputData, "LASTNAME").empty()))
		{
			strLastname = Utility::getValueFromMap(cmd.m_InputData, "LASTNAME");
		}
		if (!(Utility::getValueFromMap(cmd.m_InputData, "PASSWORD").empty()))
		{
			strPassword = Utility::getValueFromMap(cmd.m_InputData, "PASSWORD");
		}
		
		query = "UPDATE employee SET FIRSTNAME = ? , LASTNAME = ? , PASSWORD = ? WHERE USERNAME = ?";
		db.Update(query, { "S:" + strFirstName, "S:" + strLastname, "S:" + strPassword, "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Employee Record Updated Successfully";
		return res;
	}
	catch (exception e)
	{
		cout << "ERR:" << e.what();
	}
}


ResultSet* EmployeeDataHandler::ModifyEmployeeDetails(Command cmd) const
{
	int nOld_role_id;
	int nOld_location_id;
	int nLocation_id;
	int nRole_id;
	string strPassword;
	std::string query = "select PASSWORD,ROLE_ID,LOCATION_ID from employee where USERNAME=?";
	Database db = Database::Instance();
	std::vector<std::vector<string>> employeeResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });	
	
	if (employeeResult.size() > 0) 
	{
		strPassword = employeeResult[0][0].c_str();
		nOld_role_id = atoi(employeeResult[0][1].c_str());
		nOld_location_id = atoi(employeeResult[0][2].c_str());
	}
	else 
	{
		std::string msg = "No such employee found";
		throw EAMSException(msg.c_str());
	}
	if (!(Utility::getValueFromMap(cmd.m_InputData, "PASSWORD").empty()))
	{
		strPassword = Utility::getValueFromMap(cmd.m_InputData, "PASSWORD");
	}
		
	if (!(Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME").empty()))
	{
			
		query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "LOCATION_NAME") });
			
		if (Lid.size() > 0 && Lid[0].size() > 0)
		{
			nLocation_id = atoi(Lid[0][0].c_str());
		}
		else
		{	
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}
		nOld_location_id = nLocation_id;
				
	}

	if (!(Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME").empty()))
	{
		query = "select role.ROLE_ID from role where role.NAME=?";
		std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME")});

		if (Rid.size() > 0 && Rid[0].size() > 0)
		{
			nRole_id = atoi(Rid[0][0].c_str());
		}
		else 
		{		
			std::string msg = "No such role found";
			throw EAMSException(msg.c_str());
		}
			
		nOld_role_id = nRole_id;
	}

	ResultSet* res = new ResultSet();
	query = "UPDATE employee SET PASSWORD=?,ROLE_ID=?,LOCATION_ID=? WHERE USERNAME=?";
	db.Update(query, { "S:" +strPassword,"I:"+std::to_string(nOld_role_id),"I:" + std::to_string(nOld_location_id),"S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME") });
	
	res->m_IsSuccess = true;
	res->m_IsToBePrint = true;
	res->m_szPrintType = "MESSAGE";
	res->m_szMessage = "Employee Record Updated Successfully";
	return res;
}


ResultSet* EmployeeDataHandler::DeleteEmployee(Command cmd) const
{	
	if (cmd.m_InputData.size() < 1) 
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();
		std::string query = "DELETE FROM employee WHERE USERNAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "USERNAME") });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Employee Record Deleted Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::Authenticate(Command cmd) const
{
	if (cmd.m_InputData.size() != 2)
	{
		std::string msg = "Expected 2 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "SELECT employee.USERNAME, role.PRIVILEGES FROM employee INNER JOIN role ON employee.ROLE_ID = role.ROLE_ID WHERE USERNAME=? AND PASSWORD=?";
		Database db = Database::Instance();
		res->m_resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData,"USERNAME"),"S:" + Utility::getValueFromMap(cmd.m_InputData,"PASSWORD") });
		
		if (res->m_resultData.size() > 0)
		{
			res->m_IsSuccess = true;
			res->m_IsToBePrint = true;
			res->m_szPrintType = "MESSAGE";
			res->m_szMessage = "Authentication Completed Successfully";
			return res;
		}
		else 
		{
			std::string msg = "Invalid Employee Record";
			throw EAMSException(msg.c_str());
		}
		
	}	
}

