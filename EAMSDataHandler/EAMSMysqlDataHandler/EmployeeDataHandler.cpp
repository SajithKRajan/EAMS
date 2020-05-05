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
		default:
			break;
	}
	return ResultSet();
}


void EmployeeDataHandler::addEmployee(Employee employee) const
{
	std::cout << "addEmployee - > execute";
}


Employee EmployeeDataHandler::readEmployee(int id) const
{
	return Employee();
}


void EmployeeDataHandler::updateEmployee(Employee employee) const
{
}


void EmployeeDataHandler::deleteEmployee(int id) const
{
}


bool EmployeeDataHandler::authenticate(std::string username, std::string password) const
{
	std::cout << "authenticate - > execute";
	return false;
}
