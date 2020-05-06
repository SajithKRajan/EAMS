#include "AttendanceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet AttendanceDataHandler::execute(Command* cmd) const
{
	std::cout << "AttendanceDataHandler - > execute";
	switch (Utility::str2int(cmd->command_name)) {
		case Utility::str2int("ADD_CHECK-IN"):
			addCheckIn(Attendance());
			break;
		case Utility::str2int("ADD_CHECK-OUT"):
			addCheckOut(Attendance());
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_WEEK"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_EMPLOYEE_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_CURRENT_MONTH"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_ATTENDANCE_SUMMARY_OF_A_LOCATION"):
			readLocationAttendance("");
			break;
		case Utility::str2int("VIEW_EMPLOYEE_WORK_HOURS"):
			readAttendance("");
			break;
		case  Utility::str2int("VIEW_WORK_HOURS"):
			readAttendance("");
			break;
		case Utility::str2int("VIEW_TOTAL_WORK_HOURS_OF_A_LOCATION"):
			readLocationAttendance("");
			break;
		case Utility::str2int("VIEW_ORGANIZATION_WORK_HOURS"):
			readAttendance("");
			break;
		default:
			break;
	}
	return ResultSet();
}


void AttendanceDataHandler::addCheckIn(Attendance attendance) const
{
	std::cout << "Add CHECK_IN - > execute";
}
void AttendanceDataHandler::addCheckOut(Attendance attendance) const
{
	std::cout << "Add CHECK_OUT - > execute";
}

Attendance AttendanceDataHandler::readAttendance(string username) const
{
	std::cout << "Read Attendance - > execute";
	return Attendance();
}

Attendance AttendanceDataHandler::readLocationAttendance(std::string locationName) const
{
	std::cout << "Read Location Attendance - > execute";
	return Attendance();
}
