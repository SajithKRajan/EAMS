#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Employee.h"

class EmployeeDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;

private:
	ResultSet* AddEmployee(Command cmd) const;
	ResultSet* ReadEmployee(Command cmd) const;
	ResultSet* ReadEmployeeList()const;
	ResultSet* UpdateEmployee(Command cmd) const;
	ResultSet* ModifyEmployeeDetails(Command cmd) const;
	ResultSet* DeleteEmployee(Command cmd) const;
	ResultSet* Authenticate(Command cmd) const;
};

