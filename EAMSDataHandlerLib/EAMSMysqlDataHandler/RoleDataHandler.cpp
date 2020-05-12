#include "RoleDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet RoleDataHandler::execute(Command* cmd) const
{

	ResultSet* res = new ResultSet();
	try {
		switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("ADD_ROLE"):
			addRole(cmd);
			break;
		case Utility::str2int("MODIFY_ROLE"):
			updateRole(cmd);
			break;
		case Utility::str2int("VIEW_ROLE_LIST"):
			readRoleList();
			break;
		case Utility::str2int("VIEW_ROLE"):
			readRole(cmd);
			break;

		case  Utility::str2int("REMOVE_ROLE"):
			deleteRole(cmd);
			break;
	
		default:
			cout << "Please Enter Valid Commands" << endl;
			break;
		}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return ResultSet();
}


ResultSet* RoleDataHandler::addRole(Command* cmd) const
{
	if (cmd->inputs.size() != 2) {
		std::string msg = "Expected 2 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();

		std::string query = "INSERT INTO role(NAME,PRIVILEGES) VALUES (?,?)";
		Database db = Database::Instance();
		db.Insert(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "NAME"), "S:" + Utility::getValueFromMap(cmd->inputdata, "PRIVILEGES") });
		//cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Added Successfully";
		return res;
	}

}


ResultSet* RoleDataHandler::readRole(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	std::string query = "select * from role where NAME=?";
	Database db = Database::Instance();
	res->resultData = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "NAME") });
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
	return res;

}

ResultSet* RoleDataHandler::updateRole(Command* cmd) const
{
	if (cmd->inputs.size() != 3) {
		std::string msg = "Expected 3 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "UPDATE role SET NAME=? PRIVILEGES=? WHERE ROLE_ID=?";
		Database db = Database::Instance();
		db.Update(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "NEW_LOCATIONNAME"), "S:" + Utility::getValueFromMap(cmd->inputdata, "OLD_LOCATIONNAME") });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Updated Successfully";
		return res;
	}
}


ResultSet* RoleDataHandler::deleteRole(Command* cmd) const
{
	if (cmd->inputs.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		// Write code for getting locationid, role id from their names.
		std::string query = "DELETE FROM role WHERE NAME=?";
		Database db = Database::Instance();
		db.Delete(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "NAME")});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Role Record Removed Successfully";
		return res;
	}
}
