#pragma once
#include "Entities/Command.h"
#include "Entities/ResultSet.h"
#include "Common/IDataHandler.h"
#include "Entities/Absence.h"

class AbsenceDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	ResultSet* addAbsence(Command* cmd) const;
	ResultSet* readAbsence(Command* cmd) const;
};

