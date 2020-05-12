#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Employee.h"
class EmployeeDataHandler : public IDataHandler
{
public:
	virtual ResultSet* execute(Command* cmd) const;

private:
	ResultSet* addEmployee(Command* cmd) const;
	ResultSet* readEmployee(Command* cmd) const;
	ResultSet* readEmployeeList()const;
	ResultSet* updateEmployee(Command* cmd) const;
	ResultSet* modifyEmployeeDetails(Command* cmd) const;
	ResultSet* deleteEmployee(Command* cmd) const;
	ResultSet* authenticate(Command* cmd) const;
};

