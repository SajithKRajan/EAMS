#include "RoleDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet RoleDataHandler::execute(Command* cmd) const
{
	std::cout << "RoleDataHandler - > execute" << endl;
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_ROLE"):
		addRole(Role());
		break;
	case Utility::str2int("MODIFY_ROLE"):
		updateRole(Role());
		break;
	case Utility::str2int("VIEW_ROLE_LIST"):
		readRoleList();
		break;
	case Utility::str2int("VIEW_ROLE"):
		readRole("");
		break;

	case  Utility::str2int("REMOVE_ROLE"):
		deleteRole("");
		break;
	
	default:
		cout << "Please Enter Valid Commands" << endl;
		break;
	}
	return ResultSet();
}


void RoleDataHandler::addRole(Role role) const
{
	std::cout << "addRole - > execute" << endl;
}


Role RoleDataHandler::readRole(std::string roleName) const
{
	std::cout << "readRole - > execute" << endl;
	return Role();
}
Role RoleDataHandler::readRoleList() const
{
	std::cout << "readRoleList - > execute" << endl;
	return Role();
}

void RoleDataHandler::updateRole(Role role) const
{
	std::cout << "updateRole - > execute" << endl;
}


void RoleDataHandler::deleteRole(string roleName) const
{
	std::cout << "deleteRole - > execute" << endl;
}
