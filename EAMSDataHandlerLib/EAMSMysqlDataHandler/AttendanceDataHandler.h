#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Attendance.h"


class AttendanceDataHandler : public IDataHandler
{
public:
	virtual ResultSet* execute(Command cmd) const;
private:
	ResultSet* addCheckIn(Command cmd) const;
	ResultSet* addCheckOut(Command cmd) const;
	ResultSet* readAttendanceSummaryOfWeek(Command cmd) const;
	ResultSet* readAttendanceSummaryOfMonth(Command cmd) const;
	ResultSet* readLocationAttendance(Command cmd) const;
	ResultSet* readWorkHours(Command cmd) const;
	ResultSet* readLocationWorkHours(Command cmd) const;
	ResultSet* readOrganizationWorkHours() const;
};
