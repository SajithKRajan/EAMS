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


ResultSet RoleDataHandler::addRole(Role role) const
{
	//std::cout << "addRole - > execute" << endl;
	cout << "Role Record Added Successfully" << endl;
	return ResultSet();
}


ResultSet RoleDataHandler::readRole(std::string roleName) const
{
	cout << "ROLE_ID	:	" << RoleID << endl;
	cout << "ROLE NAME	:	" << roleName << endl;
	cout << "PRIVILEGES	:	" << Privileges << endl;
	//cout << "Role Record Added Successfully" << endl;
	return ResultSet();
}
ResultSet RoleDataHandler::readRoleList() const
{
	ResultSet objResultSet;
	objResultSet.printType = "TABLE";
	objResultSet.ColumnNames = { "ROLE_ID","ROLE_NAME"};
	objResultSet.resultData = { {"1","ADMIN"},{"2","EMPLOYEE"} };
	//cout << "Role Record Added Successfully" << endl;
	return ResultSet();

}

ResultSet RoleDataHandler::updateRole(Role role) const
{
	cout << "Role Record Updated Successfully" << endl;
	return ResultSet();
}


ResultSet RoleDataHandler::deleteRole(string roleName) const
{
	cout << "Role Record Removed Successfully" << endl;
	return ResultSet();
}
