#include "AttendanceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet AttendanceDataHandler::execute(Command* cmd) const
{
	std::cout << "AttendanceDataHandler - > execute";
	switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("ADD_CHECK-IN"):
			addAttendance(Attendance());
			break;
		case Utility::str2int("ADD_CHECK-OUT"):
			addAttendance(Attendance());
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendance("");
			break;
		case  Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION"):
			readAttendance("");
			break;
			break;
		case Utility::str2int("VIEW_EMPLOYEE_WORK_HOURS"):
			readAttendance("");
			break;
		case  Utility::str2int("VIEW_WORK_HOURS"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_TOTAL_WORK_HOURS_OF_A_LOCATION"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ORGANIZATION_WORK_HOURS"):
			readAttendance("");
			break;
		default:
			break;
	}
	return ResultSet();
}


void AttendanceDataHandler::addAttendance(Attendance attendance) const
{
	std::cout << "Add attendance - > execute";
}


Attendance AttendanceDataHandler::readAttendance(string username) const
{
	std::cout << "Read Attendance - > execute";
	return Attendance();
}
