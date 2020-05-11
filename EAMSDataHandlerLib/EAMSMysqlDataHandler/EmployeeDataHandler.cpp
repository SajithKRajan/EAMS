#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include <EAMSMysqlDataHandler/EAMSException.h>


ResultSet EmployeeDataHandler::execute(Command* cmd) const
{
	//std::cout << "EmployeeDataHandler - > execute"<<endl;
	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("LOGIN"):
			return authenticate("", "");
			break;
		case Utility::str2int("ADD_EMPLOYEE"):
			addEmployee(cmd);
			break;
		case Utility::str2int("EDIT_EMPLOYEE"):
			updateEmployee(Employee());
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			readEmployee(Utility::getValueFromMap(cmd->inputdata, "USERNAME"));
			break;
		case Utility::str2int("VIEW_DETAILS"):
			readEmployee("");
			break;
		case Utility::str2int("MODIFY_EMPLOYEE_DETAILS"):
			modifyEmployeeDetails(Employee());
			break;
		case Utility::str2int("REMOVE_EMPLOYEE_DETAILS"):
			deleteEmployee("");
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
		// Write code for getting locationid, role id from their names.
		std::string query = "INSERT INTO employee(USERNAME,PASSWORD,ROLE_ID,LOCATION_ID) VALUES (?,?,?,?)";
		Database db = Database::Instance();
		db.Insert(query, { "S:"+ Utility::getValueFromMap(cmd->inputdata,"USERNAME"),"S:"+ Utility::getValueFromMap(cmd->inputdata, "PASSWORD"),"I:"+ std::to_string(1),"I:"+ std::to_string(1) });
		//cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Added Successfully";
		return res;
	}
}


ResultSet* EmployeeDataHandler::readEmployee(string username) const
{
	//std::cout << "READEmployee - > execute" << endl;
	/*cout <<"USERNAME		:	" << username << endl;
	cout <<"FIRST NAME		:	" << "firstName" << endl;
	cout <<"LAST NAME		:	" << "lastName" << endl;
	cout <<"LOCATION		:	" << "locationName" << endl;
	cout <<"ROLE			:	" << "RoleName" << endl;*/
	ResultSet* res = new ResultSet();
	std::string query = "select * from employee where USERNAME=?";
	Database db = Database::Instance();
	res->resultData = db.Get(query, { "S:jeslinuser" });
	res->isSuccess = true;
	res->isToBePrint = true;
	res->printType = "OBJECT";
	return res;
}


ResultSet EmployeeDataHandler::updateEmployee(Employee employee) const
{
	
	std::string query = "UPDATE employee SET FIRSTNAME=?,LASTNAME=?,PASSWORD=? WHERE USERNAME=?";
	//std::string query = "UPDATE employee SET LOCATION_NAME=?  WHERE USERNAME=?";
	Database db = Database::Instance();
	db.Update(query, { "S:jeslin","S:raju","S:password1","S:jeslinuser" });
	cout << "Employee Record Edited Successfully" << endl;
	return ResultSet();
}

ResultSet EmployeeDataHandler::modifyEmployeeDetails(Employee employee) const
{

	std::string query = "UPDATE employee SET PASSWORD=?,ROLE_ID=?,LOCATION_NAME=? WHERE USERNAME=?";
	//std::string query = "UPDATE employee SET LOCATION_NAME=?  WHERE USERNAME=?";
	Database db = Database::Instance();
	db.Update(query, { "S:Password2","I:2","S:TVM","S:jeslinUSER" });
	cout << "Employee Record Edited Successfully" << endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::deleteEmployee(string username) const
{	
	try {
		std::string query = "DELETE FROM employee WHERE USERNAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:changed username" });
		cout << "Employee Record Deleted Successfully" << endl;
		return ResultSet();
	}
	catch (exception e)
	{
		cout << "ERR:" << e.what() << endl;
	}
}


ResultSet EmployeeDataHandler::authenticate(std::string username, std::string password) const
{
	cout << "Authentication Completed Successfully" << endl;
	return ResultSet();
	//return false;
}
