#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "IDataHandler.h"
#include "Entities/Role.h"


class RoleDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addRole(Role role) const;
	Role readRole() const;
	void updateRole(Role role) const;
	void deleteRole(std::string roleName) const;
};


