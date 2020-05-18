#include "pch.h"
#include "Location.h"

int Location::getLocationId()
{
	return this->m_nLocationId;
}

void Location::setLocationId(int LocationId)
{
	this->m_nLocationId = LocationId;
}

std::string Location::getName()
{
	return this->m_strLocationName;
}

void Location::setName(std::string Name)
{
	this->m_strLocationName = Name;
}
