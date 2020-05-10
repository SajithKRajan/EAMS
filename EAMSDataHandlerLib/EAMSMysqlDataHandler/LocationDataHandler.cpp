#include "LocationDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"

ResultSet LocationDataHandler::execute(Command* cmd) const
{
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


ResultSet LocationDataHandler::addLocation(Location location) const
{
	std::string query = "INSERT INTO location(LOCATION_NAME) VALUES (?)";;
	Database db = Database::Instance();
	db.Insert(query, { "S:BANGLORE" });
	cout << "New Location Record Added Successfully" << endl;
	return ResultSet();
}


ResultSet LocationDataHandler::readLocation() const
{
	std::string query = "select * from location";
	Database db = Database::Instance();
	db.Get(query);

	return ResultSet();
	
}


ResultSet LocationDataHandler::updateLocation(Location location) const
{
	std::string query = "UPDATE location SET LOCATION_NAME=? WHERE LOCATION_NAME=?";
	Database db = Database::Instance();
	db.Update(query, { "S:THAMILNADU","I:BANGLORE" });
	cout << "Record Updated Successfully" << endl;
	return ResultSet();
}


ResultSet LocationDataHandler::deleteLocation(string locationName) const
{
	std::string query = "DELETE FROM location WHERE LOCATION_NAME=?";
	Database db = Database::Instance();
	db.Delete(query, { "S:BANGLORE" });
	cout << "Record Removed Successfully" << endl;
	return ResultSet();
}
