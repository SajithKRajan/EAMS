#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include <EAMSMysqlDataHandler/EAMSException.h>


ResultSet EmployeeDataHandler::execute(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("LOGIN"):
			authenticate(cmd);
			break;
		case Utility::str2int("ADD_EMPLOYEE"):
			addEmployee(cmd);
			break;
		case Utility::str2int("EDIT_EMPLOYEE"):
			updateEmployee(cmd);
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			readEmployee(cmd);
			break;
		case Utility::str2int("VIEW_DETAILS"):
			readEmployee(cmd);
			break;
		case Utility::str2int("MODIFY_EMPLOYEE_DETAILS"):
			modifyEmployeeDetails(cmd);
			break;
		case Utility::str2int("REMOVE_EMPLOYEE_DETAILS"):
			deleteEmployee(cmd);
			break;
		default:
			cout << "Please Enter Valid Commands" << endl;
			break;
		}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return ResultSet();
}


ResultSet* EmployeeDataHandler::addEmployee(Command* cmd) const
{

	cout << "EmployeeDataHandler::addEmployee";
	if (cmd->inputs.size() != 4) {
		std::string msg = "Expected 4 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=? AND employee.LOCATION_ID=location.LOCATION_ID";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "LOCATION_NAME") });
		int location_id;
		if (Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such location found" << endl;
		}
		//std::cout << location_id << std::endl;
		query = "select role.ROLE_ID from role where role.NAME=? AND employee.ROLE_ID=role.ROLE_ID";
		std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "LOCATION_NAME") });
		int role_id;
		if (Rid[0].size() > 0) {
			role_id = atoi(Rid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such Role found" << endl;
		}
		//std::cout << role_id << std::endl;


		std::string insertQuery = "INSERT INTO employee(USERNAME,PASSWORD,ROLE_ID,LOCATION_ID) VALUES (?,?,?,?)";
		db.Insert(insertQuery, { "S:"+ Utility::getValueFromMap(cmd->inputdata,"USERNAME"),"S:"+ Utility::getValueFromMap(cmd->inputdata, "PASSWORD"),"I:"+ role_id,"I:"+ location_id });
		//cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Added Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::readEmployee(Command* cmd) const
{
	if (cmd->inputs.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select * from employee where USERNAME=?";
		Database db = Database::Instance();
		res->resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata,"USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "OBJECT";
		return res;
	}
}


ResultSet* EmployeeDataHandler::updateEmployee(Command* cmd) const
{
	if (cmd->inputs.size() != 3) {
		std::string msg = "Expected 3 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "UPDATE employee SET FIRSTNAME = ? , LASTNAME = ? , PASSWORD = ? WHERE USERNAME = ?";
		Database db = Database::Instance();
		db.Update(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "FIRSTNAME"), "S:" + Utility::getValueFromMap(cmd->inputdata, "LASTNAME"), "S:" + Utility::getValueFromMap(cmd->inputdata, "PASSWORD"), "S:" + Utility::getValueFromMap(cmd->inputdata, "USERNAME") });
		//cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Added Successfully";
		return res;
	}
}

ResultSet* EmployeeDataHandler::modifyEmployeeDetails(Command* cmd) const
{
	if (cmd->inputs.size() != 4) {
		std::string msg = "Expected 4 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where LOCATION.LOCATION_NAME=? AND employee.LOCATION_ID=location.LOCATION_ID";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "LOCATION_NAME") });
		int location_id;
		if (Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such location found" << endl;
		}
		//std::cout << location_id << std::endl;
		query = "select role.ROLE_ID from role where role.NAME=? AND employee.ROLE_ID=role.ROLE_ID";
		std::vector<std::vector<std::string>> Rid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "LOCATION_NAME") });
		int role_id;
		if (Rid[0].size() > 0) {
			role_id = atoi(Rid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such Role found" << endl;
		}
		//std::cout << role_id << std::endl;

		query = "UPDATE employee SET PASSWORD=?,ROLE_ID=?,LOCATION_ID=? WHERE USERNAME=?";
		db.Update(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "PASSWORD"), "I:"+role_id,"I:"+location_id});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Updated Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::deleteEmployee(Command* cmd) const
{	
	if (cmd->inputs.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		// Write code for getting locationid, role id from their names.
		std::string query = "DELETE FROM employee WHERE USERNAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "USERNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Deleted Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::authenticate(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	cout << "Authentication Completed Successfully" << endl;
	return res;
	
}

