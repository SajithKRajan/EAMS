#include "pch.h"
#include "Location.h"

Location::Location()
{
}

int Location::getLocationId()
{
	return this->locationid;
}

void Location::setLocationId(int locationid)
{
	this->locationid = locationid;
}

std::string Location::getName()
{
	return this->locationName;
}

void Location::setName(std::string Name)
{
	this->locationName = locationName;
}
