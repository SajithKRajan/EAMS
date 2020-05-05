#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "IDataHandler.h"
#include "Entities/Location.h"


class LocationDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addLocation(Location location);
	Location readLocation(int locationid);
	void updateLocation(Location location);
	void deleteLocation(int locationid);
};

