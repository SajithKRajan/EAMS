#pragma once
#include "Enities/Command.h"
#include "Enities/ResultSet.h"
#include "IDataHandler.h"
#include "Enities/Location.h"


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

