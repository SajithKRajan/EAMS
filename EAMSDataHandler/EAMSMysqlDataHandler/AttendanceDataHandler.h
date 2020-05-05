#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "IDataHandler.h"
#include "Entities/Attendance.h"


class AttendanceDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addAttendance(Attendance attendance) const;
	Attendance readAttendance(string username) const;

};
