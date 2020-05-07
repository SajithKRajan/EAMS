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
	void addCheckIn(Attendance attendance) const;
	void addCheckOut(Attendance attendance) const;
	Attendance readAttendance(std::string username) const;
	Attendance readLocationAttendance(std::string locationName) const;
	

};
