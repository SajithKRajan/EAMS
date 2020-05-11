#include "RoleDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"

ResultSet RoleDataHandler::execute(Command* cmd) const
{
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_ROLE"):
		addRole(Role());
		break;
	case Utility::str2int("MODIFY_ROLE"):
		updateRole(Role());
		break;
	case Utility::str2int("VIEW_ROLE_LIST"):
		return readRoleList();
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
	std::string query = "INSERT INTO role(NAME,PRIVILEGES) VALUES (?,?)";;
	Database db = Database::Instance();
	db.Insert(query, { "S:HR","S:AddEmployee/DeleteEmployee" });

	cout << "Role Record Added Successfully" << endl;
	return ResultSet();
}


ResultSet RoleDataHandler::readRole(std::string roleName) const
{
	cout << "ROLE_ID	:	" << "RoleID" << endl;
	cout << "ROLE NAME	:	" << roleName << endl;
	cout << "PRIVILEGES	:	" << "Privileges" << endl;
	
	std::string query = "select * from role where roleName=?";
	Database db = Database::Instance();
	db.Get(query, { "S:Admin" });
	return ResultSet();
}
ResultSet RoleDataHandler::readRoleList() const
{
	
	ResultSet objResultSet;
	objResultSet.isToBePrint = true;
	objResultSet.printType = "TABLE";
	objResultSet.ColumnNames = { "ROLE_ID","NAME"};
	objResultSet.resultData = { {"1","ADMIN"},{"2","EMPLOYEE"} };

	/*std::string query = "select * from role";
	Database db = Database::Instance();
	db.Get(query);
	return ResultSet();*/

}

ResultSet RoleDataHandler::updateRole(Role role) const
{
	std::string query = "UPDATE role SET NAME=? PRIVILEGES=? WHERE ROLE_ID=?";
	Database db = Database::Instance();
	db.Update(query, { "S:modify","S:HR","I:5" });
	cout << "Role Record Updated Successfully" << endl;
	return ResultSet();
}


ResultSet RoleDataHandler::deleteRole(string roleName) const
{
	std::string query = "DELETE FROM role WHERE ROLE_NAME=?";
	Database db = Database::Instance();
	db.Delete(query, { "S:HR" });
	cout << "Role Record Removed Successfully" << endl;
	return ResultSet();
}
