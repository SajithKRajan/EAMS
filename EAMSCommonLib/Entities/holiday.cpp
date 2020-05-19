#include "pch.h"
#include "Holiday.h"

int Holiday::GetHolidayId()
{
	return this->m_nHolidayId;
}

void Holiday::SetHolidayId(int HolidayId)
{
	this->m_nHolidayId = HolidayId;
}

int Holiday::GetLocatioId()
{
	return this->m_nLocationId;
}

void Holiday::SetLocationId(int LocationId)
{
	this->m_nLocationId = LocationId;
}

std::string Holiday::GetDescription()
{
	return this->m_strDescription;
}

void Holiday::SetDescription(std::string Description)
{
	this->m_strDescription = Description;
}
