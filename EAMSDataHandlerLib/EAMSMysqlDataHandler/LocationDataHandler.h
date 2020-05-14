#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Location.h"


class LocationDataHandler : public IDataHandler
{
public:
	virtual ResultSet* execute(Command cmd) const;
private:
	ResultSet* addLocation(Command cmd) const;
	ResultSet* readLocation() const;
	ResultSet* updateLocation(Command cmd) const;
	ResultSet* deleteLocation(Command cmd) const;
};

