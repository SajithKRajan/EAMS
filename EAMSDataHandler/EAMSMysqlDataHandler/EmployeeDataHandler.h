#pragma once
#include "Enities/Command.h"
#include "Enities/ResultSet.h"
#include "IDataHandler.h"
#include "Enities/Employee.h"

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

