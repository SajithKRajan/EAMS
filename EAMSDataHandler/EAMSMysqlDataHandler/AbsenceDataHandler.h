#pragma once
#include "Enities/Command.h"
#include "Enities/ResultSet.h"
#include "IDataHandler.h"
#include "Enities/Absence.h"

class AbsenceDataHandler : public IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const;
private:
	void addAbsence(Absence absence);
	Absence readAbsence(int absenceId);
};

