#include "pch.h"
#include "Role.h"

std::string Role::getRoleName()
{
	return this->roleName;
}

void Role::setRoleName(std::string roleName)
{
	this->roleName = roleName;
}

std::vector<std::string> Role::getPrivileges()
{
	return this->privileges;
}


void Role::setPrivileges(const std::vector<std::string>& privilege)
{
	this->privileges = privilege;
}

int Role::getRoleId()
{
	return this->roleId;
}

void Role::setRoleId(int roleId)
{
	this->roleId = roleId;
}
