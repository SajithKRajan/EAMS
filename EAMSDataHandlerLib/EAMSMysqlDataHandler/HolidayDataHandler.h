#pragma once
//Handles all functionalities of holiday class
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Holiday.h"

class HolidayDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;
private:
	ResultSet* AddHoliday(Command cmd) const;
	ResultSet* ReadHoliday(Command cmd) const;
	ResultSet* DeleteHoliday(Command cmd) const;
};


