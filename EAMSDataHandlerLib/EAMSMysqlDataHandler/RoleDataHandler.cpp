#include "RoleDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

//Execute methods corresponds to command name
ResultSet* RoleDataHandler::Execute(Command cmd) const
{

	ResultSet* res = new ResultSet();
	try 
	{
		switch (Utility::str2int(cmd.m_szCommandName)) 
		{
			case Utility::str2int("ADD_ROLE"):
				return AddRole(cmd);
				break;
			case Utility::str2int("MODIFY_ROLE"):
				return UpdateRole(cmd);
				break;
			case Utility::str2int("VIEW_ROLE_LIST"):
				return ReadRoleList();
				break;
			case Utility::str2int("VIEW_ROLE"):
				return ReadRole(cmd);
				break;
			case  Utility::str2int("REMOVE_ROLE"):
				return DeleteRole(cmd);
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


ResultSet* RoleDataHandler::AddRole(Command cmd) const
{
	if (cmd.m_InputData.size() < 2)
	{
		std::string msg = "Expected 2 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		ResultSet* res = new ResultSet();
		std::string query = "select * from role where NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> TestResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });
		
		if (TestResult.size() == 0)
		{
			std::string query = "INSERT INTO role(NAME,PRIVILEGES) VALUES (?,?)";
			Database db = Database::Instance();
			db.Insert(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME"), "S:" + Utility::getValueFromMap(cmd.m_InputData, "PRIVILEGES") });
			
			res->m_IsSuccess = true;
			res->m_IsToBePrint = true;
			res->m_szPrintType = "MESSAGE";
			res->m_szMessage = "Role Record Added Successfully";
			return res;
		}
		else
		{
			std::string msg = "Record Already exist";
			throw EAMSException(msg.c_str());
		}
	}
}


ResultSet* RoleDataHandler::ReadRole(Command cmd) const
{
	ResultSet* res = new ResultSet();
	std::string query = "select  ROLE_ID,NAME from role where NAME=?";
	Database db = Database::Instance();
	res->m_resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });

	if (res->m_resultData.size() > 0)
	{
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "TABLE";
		res->m_ColumnNames = { "ROLE_ID","NAME" };
		return res;
	}
	else 
	{
		std::string msg = "No such role found";
		throw EAMSException(msg.c_str());
	}
}


ResultSet* RoleDataHandler::ReadRoleList() const
{
	ResultSet* res = new ResultSet();
	std::string query = "select ROLE_ID,NAME from role";
	Database db = Database::Instance();
	res->m_resultData = db.Get(query);

	res->m_IsSuccess = true;
	res->m_IsToBePrint = true;
	res->m_szPrintType = "TABLE";
	res->m_ColumnNames = { "ROLE_ID","NAME"};
	return res;
}


ResultSet* RoleDataHandler::UpdateRole(Command cmd) const
{
	if (cmd.m_InputData.size() < 1)
	{
		std::string msg = "Expected 3 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else 
	{
		string strRoleName;
		string strPrivileges;

		ResultSet* res = new ResultSet();
		
		std::string query = "select NAME,PRIVILEGES from role where NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> RoleResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });
		
		if (RoleResult.size() > 0 ) 
		{
			strRoleName = RoleResult[0][0].c_str();
			strPrivileges = RoleResult[0][1].c_str();
		}
		else
		{
			std::string msg = "No such role found";
			throw EAMSException(msg.c_str());
		}

		if (!Utility::getValueFromMap(cmd.m_InputData, "NEW_ROLE_NAME").empty() && (Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") ==strRoleName))
		{
			strRoleName = Utility::getValueFromMap(cmd.m_InputData, "NEW_ROLE_NAME");
		}
		if (!Utility::getValueFromMap(cmd.m_InputData, "PRIVILEGES").empty())
		{	
			strPrivileges = strPrivileges.append(",");
			strPrivileges = strPrivileges.append(Utility::getValueFromMap(cmd.m_InputData, "PRIVILEGES"));
		}

		query = "UPDATE role SET NAME=?,PRIVILEGES=? WHERE NAME=?";
		db.Update(query, { "S:" + strRoleName , "S:"+ strPrivileges,"S:"+ Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });
		
		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Role Record Updated Successfully";
		return res;
	}
}


ResultSet* RoleDataHandler::DeleteRole(Command cmd) const
{
	if (cmd.m_InputData.size() < 1)
	{
		std::string msg = "Expected 1 arguments but got" + cmd.m_InputData.size();
		throw EAMSException(msg.c_str());
	}
	else
	{
		ResultSet* res = new ResultSet();
		std::string query = "DELETE FROM role WHERE NAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.m_InputData, "ROLE_NAME") });

		res->m_IsSuccess = true;
		res->m_IsToBePrint = true;
		res->m_szPrintType = "MESSAGE";
		res->m_szMessage = "Role Record Removed Successfully";
		return res;
	}
}
