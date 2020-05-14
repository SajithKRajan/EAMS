#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include <EAMSMysqlDataHandler/EAMSException.h>
using namespace std;

ResultSet* EmployeeDataHandler::execute(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("LOGIN"):
			return authenticate(cmd);
			break;
		case Utility::str2int("ADD_EMPLOYEE"):
			return addEmployee(cmd);
			break;
		case Utility::str2int("EDIT_EMPLOYEE"):
			return updateEmployee(cmd);
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			return readEmployee(cmd);
			break;
		case Utility::str2int("VIEW_DETAILS"):
			return readEmployee(cmd);
			break;
		case Utility::str2int("VIEW_EMPLOYEE_LIST"):
			return readEmployeeList();
			break;
		case Utility::str2int("MODIFY_EMPLOYEE_DETAILS"):
			return modifyEmployeeDetails(cmd);
			break;
		case Utility::str2int("REMOVE_EMPLOYEE_DETAILS"):
			return deleteEmployee(cmd);
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


ResultSet* EmployeeDataHandler::addEmployee(Command* cmd) const
{


	if (cmd->inputData.size() != 4) {
		std::string msg = "Expected 4 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size()>0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			std::string msg = "No such location found";
			throw EAMSException(msg.c_str());
		}
		query = "select role.ROLE_ID from role where role.NAME=?";
		std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "ROLE_NAME") });
		int role_id;
		if (Rid.size() > 0 && Rid[0].size() > 0) {
			role_id = atoi(Rid[0][0].c_str());
		}
		else {
			std::string msg = "No such role found";
			throw EAMSException(msg.c_str());
		}


		query = "INSERT INTO employee(USERNAME,PASSWORD,ROLE_ID,LOCATION_ID) VALUES (?,?,?,?)";
		db.Insert(query,{ "S:"+ Utility::getValueFromMap(cmd->inputData,"USERNAME"),"S:"+ Utility::getValueFromMap(cmd->inputData, "PASSWORD"),"I:" + std::to_string(role_id),"I:" + std::to_string(location_id)});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Added Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::readEmployee(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select EMP_ID,USERNAME,FIRSTNAME,LASTNAME,ROLE_ID,LOCATION_ID from employee where USERNAME=?";
		Database db = Database::Instance();
		res->resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData,"USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->ColumnNames = { "EMPLOYEE ID","USERNAME","FIRSTNAME","LASTNAME","ROLE_ID","LOCATION_ID" };
		res->printType = "TABLE";
		return res;
	}
}
ResultSet* EmployeeDataHandler::readEmployeeList() const
{
		try{
			ResultSet* res = new ResultSet();
			std::string query = "select EMP_ID,USERNAME,FIRSTNAME,LASTNAME,ROLE_ID,LOCATION_ID from employee";
			Database db = Database::Instance();
			res->resultData = db.Get(query);
			res->isSuccess = true;
			res->isToBePrint = true;
			res->ColumnNames = { "EMPLOYEE ID","USERNAME","FIRSTNAME","LASTNAME","ROLE_ID","LOCATION_ID" };
			res->printType = "TABLE";
			return res;
		}
		catch (exception e)
		{
			cout << "ERR:"<<e.what();
		}
}

ResultSet* EmployeeDataHandler::updateEmployee(Command* cmd) const
{

	try
	{
		std::string firstName;
		std::string lastname;
		std::string password;
		ResultSet* res = new ResultSet();
		std::string query = "select FIRSTNAME,LASTNAME,PASSWORD from employee where USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> employeeResult = db.Get(query, {"S:" +Utility::getValueFromMap(cmd->inputData,"USERNAME") });
		if (employeeResult.size() > 0) {
			firstName = employeeResult[0][0].c_str();
			lastname = employeeResult[0][1].c_str();
			password = employeeResult[0][2].c_str();
			
		}
		else {
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		if (!(Utility::getValueFromMap(cmd->inputData, "FIRSTNAME").empty()))
		{
			firstName = Utility::getValueFromMap(cmd->inputData, "FIRSTNAME");
		}
		if (!(Utility::getValueFromMap(cmd->inputData, "LASTNAME").empty()))
		{
			lastname = Utility::getValueFromMap(cmd->inputData, "LASTNAME");
		}
		if (!(Utility::getValueFromMap(cmd->inputData, "PASSWORD").empty()))
		{
			password = Utility::getValueFromMap(cmd->inputData, "PASSWORD");
		}
		
		query = "UPDATE employee SET FIRSTNAME = ? , LASTNAME = ? , PASSWORD = ? WHERE USERNAME = ?";
		db.Update(query, { "S:" +firstName, "S:" +lastname, "S:" +password, "S:" + Utility::getValueFromMap(cmd->inputData,"USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Updated Successfully";
		return res;
	}
	catch (exception e)
	{
		cout << "ERR:" << e.what();
	}
}

ResultSet* EmployeeDataHandler::modifyEmployeeDetails(Command* cmd) const
{
		std::string query = "select PASSWORD,ROLE_ID,LOCATION_ID from employee where USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> employeeResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData,"USERNAME") });
		string password;
		int Old_role_id;
		int Old_location_id;
		int location_id;
		int role_id;
		if (employeeResult.size() > 0) {
			password = employeeResult[0][0].c_str();
			Old_role_id = atoi(employeeResult[0][1].c_str());
			Old_location_id = atoi(employeeResult[0][2].c_str());

		}
		else {
			std::string msg = "No such employee found";
			throw EAMSException(msg.c_str());
		}
		if (!(Utility::getValueFromMap(cmd->inputData, "PASSWORD").empty()))
		{
			password = Utility::getValueFromMap(cmd->inputData, "PASSWORD");
		}
		
		if (!(Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME").empty()))
		{
			
			query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		
			std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME") });
			
			if (Lid.size() > 0 && Lid[0].size() > 0) {
				location_id = atoi(Lid[0][0].c_str());
			}
			else {
				
				std::string msg = "No such location found";
				throw EAMSException(msg.c_str());
			}
			Old_location_id = location_id;
			
			
		}

		if (!(Utility::getValueFromMap(cmd->inputData, "ROLE_NAME").empty()))
		{
			query = "select role.ROLE_ID from role where role.NAME=?";
			std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "ROLE_NAME") });
			if (Rid.size() > 0 && Rid[0].size() > 0) {
				role_id = atoi(Rid[0][0].c_str());
			}
			else {
				
				std::string msg = "No such role found";
				throw EAMSException(msg.c_str());
			}
			
			Old_role_id = role_id;
		}
		ResultSet* res = new ResultSet();
		query = "UPDATE employee SET PASSWORD=?,ROLE_ID=?,LOCATION_ID=? WHERE USERNAME=?";
		db.Update(query, { "S:" +password,"I:"+std::to_string(Old_role_id),"I:" + std::to_string(Old_location_id),"S:" + Utility::getValueFromMap(cmd->inputData,"USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Updated Successfully";
		return res;
}


ResultSet* EmployeeDataHandler::deleteEmployee(Command* cmd) const
{	
	if (cmd->inputData.size() < 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "DELETE FROM employee WHERE USERNAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Deleted Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::authenticate(Command* cmd) const
{
	if (cmd->inputData.size() != 2) {
		std::string msg = "Expected 2 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "SELECT employee.USERNAME, role.PRIVILEGES FROM employee INNER JOIN role ON employee.ROLE_ID = role.ROLE_ID WHERE USERNAME=? AND PASSWORD=?";
		Database db = Database::Instance();
		res->resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData,"USERNAME"),"S:" + Utility::getValueFromMap(cmd->inputData,"PASSWORD") });
		if (res->resultData.size() > 0)
		{
			res->isSuccess = true;
			res->isToBePrint = true;
			res->printType = "MESSAGE";

			res->message = "Authentication Completed Successfully";
			return res;
		}
		else {
			std::string msg = "Invalid Employee Record";
			throw EAMSException(msg.c_str());
			exit(0);
		}
		
	}

	
}

