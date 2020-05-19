#include "pch.h"
#include "Role.h"


void Role::setRoleName(std::string roleName)
{
	this->m_strRoleName = roleName;
}
std::string Role::getRoleName()
{
	return this->m_strRoleName;
}




void Role::setPrivileges(const std::vector<std::string>& privilege)
{
	this->m_Privileges = privilege;
}
std::vector<std::string> Role::getPrivileges()
{
	return this->m_Privileges;
}


void Role::setRoleId(int roleId)
{
	this->m_nRoleId = roleId;
}
int Role::getRoleId()
{
	return this->m_nRoleId;
}

