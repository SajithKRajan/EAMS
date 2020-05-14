#include "RoleDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet* RoleDataHandler::execute(Command cmd) const
{

	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd.command_name)) {
		case Utility::str2int("ADD_ROLE"):
			return addRole(cmd);
			break;
		case Utility::str2int("MODIFY_ROLE"):
			return updateRole(cmd);
			break;
		case Utility::str2int("VIEW_ROLE_LIST"):
			return readRoleList();
			break;
		case Utility::str2int("VIEW_ROLE"):
			return readRole(cmd);
			break;

		case  Utility::str2int("REMOVE_ROLE"):
			return deleteRole(cmd);
			break;
	
		default:
			cout << "Please Enter Valid Commands" << endl;
			break;
		}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return res;
}


ResultSet* RoleDataHandler::addRole(Command cmd) const
{
	if (cmd.inputData.size() != 2) {
		std::string msg = "Expected 2 arguments but got" + cmd.inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();

		std::string query = "INSERT INTO role(NAME,PRIVILEGES) VALUES (?,?)";
		Database db = Database::Instance();
		db.Insert(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "ROLE_NAME"), "S:" + Utility::getValueFromMap(cmd.inputData, "PRIVILEGES") });
		cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Added Successfully";
		cout << "added" << endl;
		return res;
	}

}


ResultSet* RoleDataHandler::readRole(Command cmd) const
{
	ResultSet* res = new ResultSet();
	std::string query = "select * from role where NAME=?";
	Database db = Database::Instance();
	res->resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "NAME") });
	res->isSuccess = true;
	res->isToBePrint = true;
	res->printType = "TABLE";
	return res;
}
ResultSet* RoleDataHandler::readRoleList() const
{
	ResultSet* res = new ResultSet();
	std::string query = "select * from role";
	Database db = Database::Instance();
	res->resultData = db.Get(query);
	res->isSuccess = true;
	res->isToBePrint = true;
	res->printType = "TABLE";
	res->ColumnNames = { "ROLE_ID","NAME","PRIVILEGES" };
	return res;

}

ResultSet* RoleDataHandler::updateRole(Command cmd) const
{
	if (cmd.inputData.size() < 1) {
		std::string msg = "Expected 3 arguments but got" + cmd.inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		string roleName;
		string privileges;
		string newRole;
		std::string query = "select NAME,PRIVILEGES from role where NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<string>> RoleResult = db.Get(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "ROLE_NAME") });
		if (RoleResult.size() > 0 ) {
			roleName = RoleResult[0][0].c_str();
			privileges= RoleResult[0][1].c_str();
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such role found" << endl;
		}
		if (!Utility::getValueFromMap(cmd.inputData, "NEW_ROLE_NAME").empty() && (Utility::getValueFromMap(cmd.inputData, "ROLE_NAME") ==roleName))
		{
			roleName = Utility::getValueFromMap(cmd.inputData, "NEW_ROLE_NAME");
		}
		if (!Utility::getValueFromMap(cmd.inputData, "PRIVILEGES").empty())
		{	
			privileges = privileges.append(",");
			privileges = privileges.append(Utility::getValueFromMap(cmd.inputData, "PRIVILEGES"));
		}
		query = "UPDATE role SET NAME=?,PRIVILEGES=? WHERE NAME=?";
		db.Update(query, { "S:" + roleName , "S:"+ privileges,"S:"+ Utility::getValueFromMap(cmd.inputData, "ROLE_NAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Updated Successfully";
		return res;
	}
}


ResultSet* RoleDataHandler::deleteRole(Command cmd) const
{
	if (cmd.inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd.inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		// Write code for getting locationid, role id from their names.
		std::string query = "DELETE FROM role WHERE NAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd.inputData, "ROLE_NAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Removed Successfully";
		return res;
	}
}
