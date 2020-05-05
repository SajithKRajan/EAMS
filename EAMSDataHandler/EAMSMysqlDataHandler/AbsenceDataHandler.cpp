#include "AbsenceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"

ResultSet AbsenceDataHandler::execute(Command* cmd) const
{
	std::cout << "AbsenceDataHandler - > execute";
	switch (Utility::str2int(cmd->command_name)) {
	case Utility::str2int("ADD_ABSENCE"):
		addAbsence(Absence());
		break;
	case Utility::str2int("VIEW_EMPLOYEE_ABSENCE_LIST"):
		readAbsence("");
		break;
	case Utility::str2int("VIEW_ABSENCE_LIST"):
		readAbsence("");
		break;
	default:
		cout << "please enter valid commands" << endl;
		break;
	}
	return ResultSet();
}

void AbsenceDataHandler::addAbsence(Absence absence) const
{
	std::cout << " ADD Absence - > execute" << endl;;
}

Absence AbsenceDataHandler::readAbsence(string username) const
{
	std::cout << " READ Absence - > execute" << endl;;

	return Absence();
}


