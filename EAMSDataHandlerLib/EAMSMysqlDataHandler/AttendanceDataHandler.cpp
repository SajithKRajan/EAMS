#include "AttendanceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"
#include "EAMSMysqlDataHandler/EAMSException.h"

ResultSet* AttendanceDataHandler::execute(Command* cmd) const
{
	ResultSet* res = new ResultSet();
	try 
	{
		switch (Utility::str2int(cmd->command_name)) {
			case Utility::str2int("ADD_CHECK-IN"):
				return addCheckIn(cmd);
				break;
			case Utility::str2int("ADD_CHECK-OUT"):
				return addCheckOut(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
				return readAttendanceSummaryOfWeek(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
				return readAttendanceSummaryOfWeek(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
				return readAttendanceSummaryOfMonth(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
				return readAttendanceSummaryOfMonth(cmd);
				break;
			case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION"):
				return readLocationAttendance(cmd);
				break;
			case Utility::str2int("VIEW_EMPLOYEE_WORK_HOURS"):
				readWorkHours(cmd);
				break;
			case  Utility::str2int("VIEW_WORK_HOURS"):
				return readWorkHours(cmd);
				break;
			case Utility::str2int("VIEW_TOTAL_WORK_HOURS_OF_A_LOCATION"):
				return readLocationWorkHours(cmd);
				break;
			case Utility::str2int("VIEW_ORGANIZATION_WORK_HOURS"):
				return readOrganizationWorkHours();
				break;
			default:
				break;
	}
	}
	catch (exception ex) {
		res->message = ex.what();
	}
	return res;
}


ResultSet* AttendanceDataHandler::addCheckIn(Command* cmd) const
{
	try{
		ResultSet* res = new ResultSet();

		std::string query = "select employee.EMP_ID,LOCATION_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:jinu"});
		int Employee_id;
		int location_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
			location_id = atoi(Empid[0][1].c_str());
		}
		else {
			cout << "ERR:No such employee found" << endl;
		}
		query = "INSERT INTO attendance(EMP_ID,LOCATION_ID,CHECK_IN) VALUES (?,?,now())";
		db.Insert(query, {"I:" + std::to_string(Employee_id),"I:" + std::to_string(location_id) });
		cout<<"Employee Record Added Successfully"<<endl;
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "MESSAGE";
		res->message = "Employee Record Added Successfully";
		return res;
	}
	catch (exception e)
	{
		cout << "ERR:" << e.what();
	}
}
ResultSet* AttendanceDataHandler::addCheckOut(Command* cmd) const
{
		try{
			ResultSet* res = new ResultSet();
			std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
			Database db = Database::Instance();
			std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:jinu" });
			int Employee_id;
			if (Empid.size() > 0 && Empid[0].size() > 0) {
				Employee_id = atoi(Empid[0][0].c_str());
			}
			else {
				cout << "ERR:No such employee found" << endl;
			}
			query = "UPDATE attendance SET CHECK_OUT=now(),TOTAL_HRS=TIMESTAMPDIFF(HOUR,attendance.CHECK_IN,attendance.CHECK_OUT) WHERE EMP_ID=? AND DATE(CHECK_IN)=CURDATE()";
			db.Update(query, { "I:" + std::to_string(Employee_id) });
			cout<<"Employee Record Added Successfully"<<endl;
			res->isSuccess = true;
			res->isToBePrint = true;
			res->printType = "MESSAGE";
			res->message = "Employee Record Added Successfully";
			return res;
		}
		catch (exception e)
		{
			cout << "ERR:" << e.what();
		}

}

ResultSet* AttendanceDataHandler::readAttendanceSummaryOfWeek(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "USERNAME") });
		int Employee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
		}
		else {
			cout << "ERR:No such employee found" << endl;
		}
		query = "select DATE(CHECK_IN) AS DATE, TIME(CHECK_IN) AS CHECK_IN, TIME(CHECK_OUT) AS CHECK_OUT from attendance where EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE()";

		res->resultData = db.Get(query, { "I:" + std::to_string(Employee_id)});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","CHECK_IN","CHECK_OUT" };
		return res;
	}
}
ResultSet* AttendanceDataHandler::readAttendanceSummaryOfMonth(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "USERNAME") });
		int Employee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
		}
		else {
			cout << "ERR:No such employee found" << endl;
		}
		query = "select DATE(CHECK_IN) AS DATE, TIME(CHECK_IN) AS CHECK_IN, TIME(CHECK_OUT) AS CHECK_OUT from attendance where EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 30 DAY) AND CURDATE()";

		res->resultData = db.Get(query, { "I:" + std::to_string(Employee_id)});
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","CHECK_IN","CHECK_OUT" };
		return res;
	}
}

ResultSet* AttendanceDataHandler::readLocationAttendance(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such location found" << endl;
		}
		query = "select DATE(CHECK_IN) AS DATE, COUNT(*) AS COUNT FROM attendance WHERE LOCATION_ID = ? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";

		res->resultData = db.Get(query, { "I:" + std::to_string(location_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","COUNT" };
		return res;
	}
}
ResultSet* AttendanceDataHandler::readWorkHours(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select employee.EMP_ID from employee where employee.USERNAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Empid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "USERNAME") });
		int Employee_id;
		if (Empid.size() > 0 && Empid[0].size() > 0) {
			Employee_id = atoi(Empid[0][0].c_str());
		}
		else {
			
			cout << "ERR:No such employee found" << endl;
		}
		query = "select DATE(CHECK_IN), TOTAL_HRS FROM attendance WHERE EMP_ID = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 30 DAY) AND CURDATE()";

		res->resultData = db.Get(query, { "I:" + std::to_string(Employee_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","TOTAL_HRS" };
		return res;
	}
}
ResultSet* AttendanceDataHandler::readLocationWorkHours(Command* cmd) const
{
	if (cmd->inputData.size() != 1) {
		std::string msg = "Expected 1 arguments but got" + cmd->inputData.size();
		throw EAMSException(msg.c_str());
	}
	else {
		ResultSet* res = new ResultSet();
		std::string query = "select location.LOCATION_ID from location where location.LOCATION_NAME=?";
		Database db = Database::Instance();
		std::vector<std::vector<std::string>> Lid = db.Get(query, { "S:" + Utility::getValueFromMap(cmd->inputData, "LOCATION_NAME") });
		int location_id;
		if (Lid.size() > 0 && Lid[0].size() > 0) {
			location_id = atoi(Lid[0][0].c_str());
		}
		else {
			//throw error role could not found.
			cout << "ERR:No such location found" << endl;
		}
		query = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS  FROM attendance WHERE LOCATION_ID=? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";

		res->resultData = db.Get(query, { "I:" + std::to_string(location_id) });
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","TOTAL_HRS" };
		return res;
	}
}
ResultSet* AttendanceDataHandler::readOrganizationWorkHours() const
{

		ResultSet* res = new ResultSet();
		std::string query = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS FROM attendance WHERE  DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
		Database db = Database::Instance();
		res->resultData = db.Get(query);
		res->isSuccess = true;
		res->isToBePrint = true;
		res->printType = "TABLE";
		res->ColumnNames = { "DATE","TOTAL_HRS" };
		return res;
}
