#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Holiday.h"


class HolidayDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet* addHoliday(Command* cmd) const;
	ResultSet* readHoliday(Command* cmd) const;
	ResultSet* deleteHoliday(Command* cmd) const;
};


