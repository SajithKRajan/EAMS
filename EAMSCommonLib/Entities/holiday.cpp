#include "pch.h"
#include "Holiday.h"

int Holiday::getHolidayId()
{
	return this->holidayid;
}

void Holiday::setHolidayId(int holidayid)
{
	this->holidayid = holidayid;
}

int Holiday::getLocatioId()
{
	return this->locationid;
}

void Holiday::setLocationId(int locationid)
{
	this->locationid = locationid;
}

std::string Holiday::getDescription()
{
	return this->description;
}

void Holiday::setDescription(std::string description)
{
	this->description = description;
}
