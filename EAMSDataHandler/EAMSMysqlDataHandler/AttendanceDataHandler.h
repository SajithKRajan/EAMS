#pragma once
#include "Enities/Command.h"
#include "Enities/ResultSet.h"
#include "IDataHandler.h"
#include "Enities/Attendance.h"


class AttendanceDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addAttendance(Attendance attendance);
	Attendance readAttendance(int attid);

};
