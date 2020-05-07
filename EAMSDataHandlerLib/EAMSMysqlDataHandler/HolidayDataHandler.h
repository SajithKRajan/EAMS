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
	void addHoliday(Holiday holiday) const;
	Holiday readHoliday(std::string locationName) const;
	void deleteHoliday(std::string locationName,std::string date) const;
};


