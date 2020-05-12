#include "AbsenceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet AbsenceDataHandler::execute(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	try {
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_ABSENCE"):
		addAbsence(cmd);
		break;
	case Utility::str2int("VIEW_EMPLOYEE_ABSENCE_LIST"):
		readAbsence(cmd);
		break;
	case Utility::str2int("VIEW_ABSENCE_LIST"):
		readAbsence(cmd);
		break;
	default:
		std::cout << "please enter valid commands" << endl;
		break;
	}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return ResultSet();
}

ResultSet* AbsenceDataHandler::addAbsence(Command* cmd) const
{
	try{
		ResultSet* res = new ResultSet();
		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:steny"});
		int Employee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
		}
		else {
			cout << "ERR:No such Employee found" << endl;
		}
		query = "INSERT INTO absence(EMP_ID,DATE) VALUES (?,now())";
		db.Insert(query,{ "I:"+std::to_string(Employee_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Absence Record Added Successfully";
		cout << "added" << endl;
		return res;
	}
	catch (exception e)
	{
		cout << "ERR:" << e.what();
	}
}

ResultSet* AbsenceDataHandler::readAbsence(Command* cmd) const
{
	if (cmd->inputs.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputs.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputdata, "USERNAME") });
		int Employee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
		}
		else {
			cout << "ERR:No such location found" << endl;
		}
		query = "select *  from absence where EMP_ID=?";
		res->resultData = db.Get(query, { "I:" + std::to_string(Employee_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->ColumnNames = { "ABS_ID","EMP_ID","DATE" };
		res->printType = "TABLE";
		return res;
	}

}


