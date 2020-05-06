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
	void addRole(Role role) const;
	Role readRoleList() const;
	Role readRole(std::string roleName) const;
	void updateRole(Role role) const;
	void deleteRole(std::string roleName) const;
};


