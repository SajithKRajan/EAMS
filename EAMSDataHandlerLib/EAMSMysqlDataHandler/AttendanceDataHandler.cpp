#include "AttendanceDataHandler.h"
#include <iostream>
#include "../pch.h"

ResultSet AttendanceDataHandler::execute(Command*) const
{
	std::cout << "AttendanceDataHandler - > execute";
	return ResultSet();
}


void AttendanceDataHandler::addAttendance(Attendance attendance)
{

}


Attendance AttendanceDataHandler::readAttendance(int Attid)
{
	return Attendance();
}
