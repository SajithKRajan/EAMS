#include "LocationDataHandler.h"
#include <iostream>
#include "../pch.h"

ResultSet LocationDataHandler::execute(Command*) const
{
	std::cout << "LocationDataHandler - > execute";
	return ResultSet();
}


void LocationDataHandler::addLocation(Location location)
{
}


Location LocationDataHandler::readLocation(int locationid)
{
	return Location();
}


void LocationDataHandler::updateLocation(Location location)
{
}


void LocationDataHandler::deleteLocation(int locationid)
{
}
