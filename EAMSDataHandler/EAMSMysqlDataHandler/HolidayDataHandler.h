#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "IDataHandler.h"
#include "Entities/Holiday.h"


class HolidayDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addHoliday(Holiday holiday);
	Holiday readHoliday(int holidayid);
	void updateHoliday(Holiday holiday);
	void deleteHoliday(int holidayid);
};


