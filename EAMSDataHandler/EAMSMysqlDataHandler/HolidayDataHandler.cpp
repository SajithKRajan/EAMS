#include "HolidayDataHandler.h"
#include <iostream>

ResultSet HolidayDataHandler::execute(Command*) const
{
	std::cout << "HolidayDataHandler - > execute";
	return ResultSet();
}


void HolidayDataHandler::addHoliday(Holiday holiday)
{
}


Holiday HolidayDataHandler::readHoliday(int holidayid)
{
	return Holiday();
}


void HolidayDataHandler::updateHoliday(Holiday holiday)
{
}


void HolidayDataHandler::deleteHoliday(int holidayid)
{
}
