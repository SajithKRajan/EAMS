#include "AbsenceDataHandler.h"
#include <iostream>


ResultSet AbsenceDataHandler::execute(Command* cmd) const
{
	std::cout << "AbsenceDataHandler - > execute";
	return ResultSet();
}

void AbsenceDataHandler::addAbsence(Absence absence)
{
}

Absence AbsenceDataHandler::readAbsence(int absenceId)
{
	return Absence();
}


