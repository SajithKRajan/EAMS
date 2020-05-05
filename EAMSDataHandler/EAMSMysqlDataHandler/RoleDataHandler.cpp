#include "RoleDataHandler.h"
#include <iostream>

ResultSet RoleDataHandler::execute(Command*) const
{
	std::cout << "RoleDataHandler - > execute";
	return ResultSet();
}


void RoleDataHandler::addRole(Role role)
{
}


Role RoleDataHandler::readRole(int roleid)
{
	return Role();
}


void RoleDataHandler::updateRole(Role role)
{
}


void RoleDataHandler::deleteRole(int roleid)
{
}
