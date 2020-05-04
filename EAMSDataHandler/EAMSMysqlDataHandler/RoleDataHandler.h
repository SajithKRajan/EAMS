#pragma once
#include "Enities/Command.h"
#include "Enities/ResultSet.h"
#include "IDataHandler.h"
#include "Enities/Role.h"


class RoleDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addRole(Role role);
	Role readRole(int roleid);
	void updateRole(Role role);
	void deleteRole(int roleid);
};


