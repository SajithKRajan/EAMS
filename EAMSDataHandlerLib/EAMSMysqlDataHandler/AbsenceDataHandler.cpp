#include "AbsenceDataHandler.h"
#include <iostream>
#include "Utilities/Utility.h"
#include "Common/Database.h"

ResultSet AbsenceDataHandler::execute(Command* cmd) const
{
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

ResultSet AbsenceDataHandler::addAbsence(Absence absence) const
{
	std::string query = "INSERT INTO absence(EMP_ID,DATE) VALUES (?,now())";
	Database db = Database::Instance();
	db.Insert(query, { "I:1" });
	cout << "Absence Added Successfully" << endl;
	return ResultSet();
}

ResultSet AbsenceDataHandler::readAbsence(string username) const
{
	std::string query = "select *  from absence where USERNAME=? ";
	Database db = Database::Instance();
	db.Get(query, { "S:jeslin" });

	return ResultSet();
}


