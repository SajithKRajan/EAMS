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
	ResultSet addHoliday(Holiday holiday) const;
	ResultSet readHoliday(std::string locationName) const;
	ResultSet deleteHoliday(std::string locationName,std::string date) const;
};


