#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "IDataHandler.h"
#include "Entities/Employee.h"

class EmployeeDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addEmployee(Employee employee) const;
	Employee readEmployee(int id) const;
	void updateEmployee(Employee employee) const;
	void deleteEmployee(int id) const;
	bool authenticate(std::string username, std::string password) const;
};

