#pragma once
//Handles all functionalities of attendance class
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Attendance.h"

class AttendanceDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;
private:
	ResultSet* AddCheckIn(Command cmd) const;
	ResultSet* AddCheckOut(Command cmd) const;
	ResultSet* ReadAttendanceSummaryOfWeek(Command cmd) const;
	ResultSet* ReadAttendanceSummaryOfMonth(Command cmd) const;
	ResultSet* ReadLocationAttendance(Command cmd) const;
	ResultSet* ReadWorkHours(Command cmd) const;
	ResultSet* ReadLocationWorkHours(Command cmd) const;
	ResultSet* ReadOrganizationWorkHours() const;
};
