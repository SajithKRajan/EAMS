#include "AttendanceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"

ResultSet AttendanceDataHandler::execute(Command* cmd) const
{
	switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("ADD_CHECK-IN"):
			addCheckIn(Attendance());
			break;
		case Utility::str2int("ADD_CHECK-OUT"):
			addCheckOut(Attendance());
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendanceSummaryOfWeek("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendanceSummaryOfWeek("");
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendanceSummaryOfMonth("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendanceSummaryOfMonth("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION"):
			readLocationAttendance("");
			break;
		case Utility::str2int("VIEW_EMPLOYEE_WORK_HOURS"):
			readWorkHours("");
			break;
		case  Utility::str2int("VIEW_WORK_HOURS"):
			readWorkHours("");
			break;
		case Utility::str2int("VIEW_TOTAL_WORK_HOURS_OF_A_LOCATION"):
			readLocationWorkHours("");
			break;
		case Utility::str2int("VIEW_ORGANIZATION_WORK_HOURS"):
			readOrganizationWorkHours();
			break;
		default:
			break;
	}
	return ResultSet();
}


ResultSet AttendanceDataHandler::addCheckIn(Attendance attendance) const
{
	std::string query = "INSERT INTO attendance(EMP_ID,LOCATION_ID,CHECK_IN) VALUES (?,?,now())";
	Database db = Database::Instance();
	db.Insert(query, { "I:3","I:1" });
	cout << "Attendance Marked Successfully" << endl;
	return ResultSet();
}
ResultSet AttendanceDataHandler::addCheckOut(Attendance attendance) const
{
	std::string query = "UPDATE attendance SET CHECK_OUT=now(),TOTAL_HRS=TIMESTAMPDIFF(HOUR,attendance.CHECK_IN,attendance.CHECK_OUT) WHERE EMP_ID=? AND DATE(CHECK_IN)=CURDATE()";
	Database db = Database::Instance();
	db.Update(query, { "I:3" });
	cout << "Attendance Marked Successfully" << endl;
	return ResultSet();
}

ResultSet AttendanceDataHandler::readAttendanceSummaryOfWeek(string username) const
{
	std::string query = "select DATE(CHECK_IN) AS DATE, TIME(CHECK_IN) AS CHECK_IN, TIME(CHECK_OUT) AS CHECK_OUT from attendance where USERNAME = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE()";
	Database db = Database::Instance();
	db.Get(query, { "S:Sajith4" });
	return ResultSet();
}
ResultSet AttendanceDataHandler::readAttendanceSummaryOfMonth(string username) const
{
	std::string query = "select DATE(CHECK_IN) AS DATE, TIME(CHECK_IN) AS CHECK_IN, TIME(CHECK_OUT) AS CHECK_OUT from attendance where USERNAME = ? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL - 30 DAY) AND CURDATE()";
	Database db = Database::Instance();
	db.Get(query, { "S:Sajith4" });
	return ResultSet();
}

ResultSet AttendanceDataHandler::readLocationAttendance(std::string locationName) const
{
	std::string query = "select DATE(CHECK_IN) AS DATE, COUNT(*) AS COUNT FROM attendance WHERE LOCATION_NAME = ? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL - 7 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
	Database db = Database::Instance();
	db.Get(query, { "S:tvm" });
	return ResultSet();
}
ResultSet AttendanceDataHandler::readWorkHours(std::string username) const
{
	std::string query = "select DATE(CHECK_IN),TOTAL_HRS FROM attendance WHERE USERNAME=? AND CHECK_IN BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE()";
	Database db = Database::Instance();
	db.Get(query, { "S:Sajith4" });
	return ResultSet();
}
ResultSet AttendanceDataHandler::readLocationWorkHours(std::string locationName) const
{
	std::string query = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS  FROM attendance WHERE LOCATION_NAME=? AND DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
	Database db = Database::Instance();
	db.Get(query, { "S:TVM" });
	return ResultSet();
}
ResultSet AttendanceDataHandler::readOrganizationWorkHours() const
{
	std::string query = "select DATE(CHECK_IN) AS DATE,SUM(TOTAL_HRS) AS TOTAL_HOURS FROM attendance WHERE  DATE(CHECK_IN) BETWEEN ADDDATE(CURDATE(), INTERVAL -30 DAY) AND CURDATE() GROUP BY DATE(CHECK_IN)";
	Database db = Database::Instance();
	db.Get(query);
	return ResultSet();
}
