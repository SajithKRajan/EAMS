#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Employee.h"

class EmployeeDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet* addEmployee(Command* cmd) const;
	ResultSet* readEmployee(std::string username) const;
	ResultSet updateEmployee(Employee employee) const;
	ResultSet modifyEmployeeDetails(Employee employee) const;
	ResultSet deleteEmployee(std::string username) const;
	ResultSet authenticate(std::string username, std::string password) const;
};

