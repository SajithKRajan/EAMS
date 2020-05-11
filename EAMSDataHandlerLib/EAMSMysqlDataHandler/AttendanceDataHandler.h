#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Attendance.h"


class AttendanceDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet addCheckIn(Attendance attendance) const;
	ResultSet addCheckOut(Attendance attendance) const;
	ResultSet readAttendanceSummaryOfWeek(std::string username) const;
	ResultSet readAttendanceSummaryOfMonth(std::string username) const;
	ResultSet readLocationAttendance(std::string locationName) const;
	ResultSet readWorkHours(std::string username) const;
	ResultSet readLocationWorkHours(std::string locationName) const;
	ResultSet readOrganizationWorkHours() const;
};
