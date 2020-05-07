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
	void addEmployee(Employee employee) const;
	Employee readEmployee(std::string username) const;
	void updateEmployee(Employee employee) const;
	void deleteEmployee(std::string username) const;
	bool authenticate(std::string username, std::string password) const;
};

