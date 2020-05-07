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
	void addLocation(Location location) const;
	Location readLocation() const;
	void updateLocation(Location location) const;
	void deleteLocation(std::string locationName) const;
};

