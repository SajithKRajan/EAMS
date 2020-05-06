#include "LocationDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet LocationDataHandler::execute(Command* cmd) const
{
	std::cout << "LocationDataHandler - > execute" << endl;
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_LOCATION"):
		addLocation(Location());
		break;
	case Utility::str2int("MODIFY_LOCATION"):
		updateLocation(Location());
		break;
	case Utility::str2int("VIEW_LOCATION_LIST"):
		readLocation();
		break;
	case  Utility::str2int("REMOVE_LOCATION"):
		deleteLocation("");
		break;
	default:
		cout << "Please Enter Valid Commands" << endl;
		break;
	}
	return ResultSet();
}


void LocationDataHandler::addLocation(Location location) const
{
	std::cout << "addLocation - > execute" << endl;
}


Location LocationDataHandler::readLocation() const
{
	std::cout << "readLocation - > execute" << endl;
	return Location();
}


void LocationDataHandler::updateLocation(Location location) const
{
	std::cout << "updateLocation - > execute" << endl;
}


void LocationDataHandler::deleteLocation(string locationName) const
{
	std::cout << "deleteLocation - > execute" << endl;
}
