#include "EmployeeDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "../pch.h"

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
	/*std::string query = "INSERT INTO employee(USERNAME,FIRSTNAME,LASTNAME,PASSWORD,ROLE_ID) VALUES (?,?,?,?,?)";
	database->Insert(query, { "S:jinuuser","S:jinu","S:I","S:jinu","I:2" });*/
	cout << "New Employee added Successfully" << endl;
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
