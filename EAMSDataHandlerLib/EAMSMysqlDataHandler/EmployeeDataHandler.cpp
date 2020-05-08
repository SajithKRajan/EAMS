#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"


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
			addEmployee(Employee());
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			readEmployee(Utility::getValueFromMap(cmd->inputdata,"USERNAME"));
			break;
		case Utility::str2int("VIEW_DETAILS"):
			readEmployee("");
			break;
		case Utility::str2int("MODIFY_EMPLOYEE_DETAILS"):
			updateEmployee(Employee());
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
	//std::cout << "addEmployee - > execute" << endl;
	cout<<"Employee Record Added Successfully"<<endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::readEmployee(string username) const
{
	//std::cout << "READEmployee - > execute" << endl;
	cout <<"USERNAME		:	" << username << endl;
	cout <<"FIRST NAME		:	" << "firstName" << endl;
	cout <<"LAST NAME		:	" << "lastName" << endl;
	cout <<"LOCATION		:	" << "locationName" << endl;
	cout <<"ROLE			:	" << "RoleName" << endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::updateEmployee(Employee employee) const
{
	//std::cout << "UpdateEmployee - > execute" << endl;
	cout << "Employee Record Updated Successfully" << endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::deleteEmployee(string username) const
{
	//std::cout << "DeleteEmployee - > execute" << endl;
	cout << "Employee Record Deleted Successfully" << endl;
	return ResultSet();
}


ResultSet EmployeeDataHandler::authenticate(std::string username, std::string password) const
{
	cout << "Authentication Completed Successfully" << endl;
	return ResultSet();
	//return false;
}
