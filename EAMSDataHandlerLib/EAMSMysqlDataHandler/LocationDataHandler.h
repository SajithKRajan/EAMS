#pragma once
//Handles all functionalities of location class
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Location.h"

class LocationDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;
private:
	ResultSet* AddLocation(Command cmd) const;
	ResultSet* ReadLocation() const;
	ResultSet* UpdateLocation(Command cmd) const;
	ResultSet* DeleteLocation(Command cmd) const;
};

