#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Role.h"


class RoleDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;
private:
	ResultSet* AddRole(Command cmd) const;
	ResultSet* ReadRoleList() const;
	ResultSet* ReadRole(Command cmd) const;
	ResultSet* UpdateRole(Command cmd) const;
	ResultSet* DeleteRole(Command cmd) const;
};


