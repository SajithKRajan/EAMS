#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"


ResultSet EmployeeDataHandler::execute(Command* cmd) const
{
	std::cout << "EmployeeDataHandler - > execute"<<endl;
	switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("LOGIN"):
			authenticate("","");
			break;
		case Utility::str2int("ADD_EMPLOYEE"):
			addEmployee(Employee());
			break;
		case Utility::str2int("EDIT_EMPLOYEE"):
			addEmployee(Employee());
			break;
		case  Utility::str2int("VIEW_EMPLOYEE_DETAILS"):
			readEmployee("");
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


void EmployeeDataHandler::addEmployee(Employee employee) const
{
	std::cout << "addEmployee - > execute" << endl;
}


Employee EmployeeDataHandler::readEmployee(string username) const
{
	std::cout << "READEmployee - > execute" << endl;
	return Employee();
}


void EmployeeDataHandler::updateEmployee(Employee employee) const
{
	std::cout << "UpdateEmployee - > execute" << endl;
}


void EmployeeDataHandler::deleteEmployee(string username) const
{
	std::cout << "DeleteEmployee - > execute" << endl;
}


bool EmployeeDataHandler::authenticate(std::string username, std::string password) const
{
	std::cout << "authenticate - > execute" << endl;
	return false;
}
