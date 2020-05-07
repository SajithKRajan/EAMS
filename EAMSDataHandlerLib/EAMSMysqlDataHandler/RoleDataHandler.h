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
	ResultSet addRole(Role role) const;
	ResultSet readRoleList() const;
	ResultSet readRole(std::string roleName) const;
	ResultSet updateRole(Role role) const;
	ResultSet deleteRole(std::string roleName) const;
};


