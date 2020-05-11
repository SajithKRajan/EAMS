#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Role.h"


class RoleDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet* addRole(Command* cmd) const;
	ResultSet* readRoleList() const;
	ResultSet* readRole(Command* cmd) const;
	ResultSet* updateRole(Command* cmd) const;
	ResultSet* deleteRole(Command* cmd) const;
};


