#pragma once
//Handles all functionalities of absence class
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Absence.h"
 
class AbsenceDataHandler : public IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command cmd) const;
private:
	ResultSet* AddAbsence(Command cmd) const;
	ResultSet* ReadAbsence(Command cmd) const;
};

