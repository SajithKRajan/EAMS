#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Location.h"


class LocationDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet addLocation(Location location) const;
	ResultSet readLocation() const;
	ResultSet updateLocation(Location location) const;
	ResultSet deleteLocation(std::string locationName) const;
};

