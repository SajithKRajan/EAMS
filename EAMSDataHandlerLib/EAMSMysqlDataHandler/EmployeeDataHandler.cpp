#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"


ResultSet EmployeeDataHandler::execute(Command* cmd) const
{
	//std::cout << "EmployeeDataHandler - > execute"<<endl;
	switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("LOGIN"):
			return authenticate("","");
			break;
		case Utility::str2int("ADD_EMPLOYEE"):
			addEmployee(Employee());
			break;
		case Utility::str2int("EDIT_EMPLOYEE"):
			updateEmployee(Employee());
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			readEmployee(Utility::getValueFromMap(cmd->inputdata,"USERNAME"));
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
	return ResultSet();
}


ResultSet EmployeeDataHandler::addEmployee(Employee employee) const
{
	std::string query = "INSERT INTO employee(USERNAME,PASSWORD,ROLE_ID,LOCATION_NAME) VALUES (?,?,?,?)";
	Database db = Database::Instance();
	db.Insert(query, { "S:jeslinuser","S:password1","I:1","S:TVM" });
	cout<<"Employee Record Added Successfully"<<endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::readEmployee(string username) const
{
	//std::cout << "READEmployee - > execute" << endl;
	/*cout <<"USERNAME		:	" << username << endl;
	cout <<"FIRST NAME		:	" << "firstName" << endl;
	cout <<"LAST NAME		:	" << "lastName" << endl;
	cout <<"LOCATION		:	" << "locationName" << endl;
	cout <<"ROLE			:	" << "RoleName" << endl;*/

	std::string query = "select * from employee where USERNAME=?";
	Database db = Database::Instance();
	db.Get(query, { "S:jeslinuser" });

	return ResultSet();
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
